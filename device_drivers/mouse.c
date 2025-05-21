#include <lcom/lcf.h>

#include "i8042.h"
#include "kbc.h"
#include "mouse.h"

int           mouse_hook_id = 3; // um valor qualquer [0..7], desde que seja diferente do teclado e do timer
uint8_t       current_byte;
uint8_t       byte_index = 0;
uint8_t       mouse_bytes[3];
struct packet mouse_packet;

int(mouse_subscribe_int)(uint8_t *bit_no) {
    // Check if bit_no is valid
    if (bit_no == NULL) return 1;

    *bit_no = BIT(mouse_hook_id);

    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int(mouse_unsubscribe_int)() {
    return sys_irqrmpolicy(&mouse_hook_id); //! Porque é que é preciso passar por referência?
}

void(mouse_ih)() {
    if (read_KBC_output(0x60, &current_byte, 1) != OK) printf("%s\n", "Error in reading current byte.");
}

void(mouse_sync_bytes)() {
    // Check if current_byte is control byte
    if ((current_byte & BIT(3)) && byte_index == 0) {
        mouse_bytes[byte_index] = current_byte;
        byte_index++;
    } else if (byte_index > 0) {
        mouse_bytes[byte_index] = current_byte;
        byte_index++;
    }
}

void(mouse_bytes_to_packet)() {
    //! C não permite atribuição direta de arrays
    for (int i = 0; i < 3; i++) mouse_packet.bytes[i] = mouse_bytes[i];

    mouse_packet.rb = mouse_bytes[0] & BIT(1);
    mouse_packet.mb = mouse_bytes[0] & BIT(2);
    mouse_packet.lb = mouse_bytes[0] & BIT(0);

    mouse_packet.x_ov = mouse_bytes[0] & BIT(6);
    mouse_packet.y_ov = mouse_bytes[0] & BIT(7);

    mouse_packet.delta_x = (mouse_bytes[0] & BIT(4)) ? (0xFF << 8) | mouse_bytes[1] : (0x00 << 8) | mouse_bytes[1];
    mouse_packet.delta_y = (mouse_bytes[0] & BIT(5)) ? (0xFF << 8) | mouse_bytes[2] : (0x00 << 8) | mouse_bytes[2];
}

int(mouse_write)(uint8_t command) {
    uint8_t attempts = 10;
    uint8_t mouse_response;

    while (attempts) {
        // Tell KBC that we want to write to the mouse
        //! Porque é que é para a port 0x64 e não para a 0x60
        if (write_KBC_command(0x64, 0xD4) != OK) return 1;

        // Write to the mouse
        if (write_KBC_command(0x60, command) != OK) return 1;

        // Check output buffer
        if (util_sys_inb(0x60, &mouse_response) != OK) return 1;

        // If successful
        if (mouse_response == ACK) return 0;
        else if (mouse_response == ERROR) return 1; // In case of error, abort

        tickdelay(micros_to_ticks(20000));
        attempts--;
    }
    return 1;
}
