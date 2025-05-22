#include <lcom/lcf.h>

#include "../utils/result.h"
#include "i8042.h"
#include "kbc.h"
#include "mouse.h"

// Global variables for mouse interrupt handling
int           mouse_hook_id = 3; // Hook ID for mouse interrupts
uint8_t       current_byte;      // Current byte read from the mouse
uint8_t       byte_index = 0;    // Index for assembling mouse packets
uint8_t       mouse_bytes[3];    // Buffer to store mouse packet bytes
struct packet mouse_packet;      // Struct to store the parsed mouse packet

/**
 * @brief Subscribes to mouse interrupts.
 * @param bit_no Pointer to store the bit number of the interrupt.
 * @return Result indicating success or specific error.
 */
Result(mouse_subscribe_int)(uint8_t *bit_no) {
    if (bit_no == NULL) return RES_INVALID_ARGUMENT;

    *bit_no = BIT(mouse_hook_id);

    if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id) != RES_OK)
        return RES_PERMISSION_ERROR;

    return RES_OK;
}

/**
 * @brief Unsubscribes from mouse interrupts.
 * @return Result indicating success or specific error.
 */
Result(mouse_unsubscribe_int)() {
    if (sys_irqrmpolicy(&mouse_hook_id) != RES_OK) return RES_PERMISSION_ERROR;
    return RES_OK;
}

/**
 * @brief Mouse interrupt handler. Reads the current byte from the mouse.
 */
void(mouse_ih)() {
    if (read_KBC_output(0x60, &current_byte, 1) != RES_OK) printf("%s\n", "Error in reading current byte.");
}

/**
 * @brief Synchronizes mouse bytes to form a complete packet.
 */
void(mouse_sync_bytes)() {
    if ((current_byte & BIT(3)) && byte_index == 0) {
        mouse_bytes[byte_index] = current_byte;
        byte_index++;
    } else if (byte_index > 0) {
        mouse_bytes[byte_index] = current_byte;
        byte_index++;
    }
}

/**
 * @brief Converts the synchronized mouse bytes into a packet structure.
 */
void(mouse_bytes_to_packet)() {
    for (int i = 0; i < 3; i++) mouse_packet.bytes[i] = mouse_bytes[i];

    mouse_packet.rb = mouse_bytes[0] & BIT(1);
    mouse_packet.mb = mouse_bytes[0] & BIT(2);
    mouse_packet.lb = mouse_bytes[0] & BIT(0);

    mouse_packet.x_ov = mouse_bytes[0] & BIT(6);
    mouse_packet.y_ov = mouse_bytes[0] & BIT(7);

    mouse_packet.delta_x = (mouse_bytes[0] & BIT(4)) ? (0xFF << 8) | mouse_bytes[1] : (0x00 << 8) | mouse_bytes[1];
    mouse_packet.delta_y = (mouse_bytes[0] & BIT(5)) ? (0xFF << 8) | mouse_bytes[2] : (0x00 << 8) | mouse_bytes[2];
}

/**
 * @brief Sends a command to the mouse.
 * @param command The command to send.
 * @return Result indicating success or specific error.
 */
Result(mouse_write)(uint8_t command) {
    uint8_t attempts = 10;
    uint8_t mouse_response;

    while (attempts) {
        if (write_KBC_command(0x64, 0xD4) != RES_OK) return RES_IO_ERROR;

        if (write_KBC_command(0x60, command) != RES_OK) return RES_IO_ERROR;

        if (read_KBC_output(0x60, &mouse_response, 1) != RES_OK) return RES_IO_ERROR;

        if (mouse_response == 0xFA) return RES_OK;

        attempts--;
    }

    return RES_TIMEOUT;
}
