#include <lcom/lcf.h>
#include "kbd.h"
#include "i8042.h"

int kbd_hook_id = 1;
uint16_t scancode = 0x00;
bool is_two_byte = false; // Flag to indicate that we are waiting for the second byte
int sys_inb_count = 0;

void (kbc_ih)() {
  uint8_t status, byte;

  // Read status register
  if(util_sys_inb(KBC_STATUS_REG, &status) != OK) return;

  
  // Check if there was some communication error
  if(status & BIT(7) || status & BIT(6)) return;
  
  
  // Check if there is no data to be read
  if(!(status & BIT(0))) return;

  if(util_sys_inb(KBC_OUT_BUF, &byte) != OK) return;

  // Check if scancode is one or two bytes long
  if(byte == 0xE0) {
    is_two_byte = true;
    return;
  }
  
  // If scancode is two bytes long, we combine the values
  if(is_two_byte) {
    scancode = (0xE0 << 8) | byte;
    is_two_byte = false; // Reset the flag
  }
  else {
    scancode = byte;
  }
}

int (kbd_subscribe_int)(uint8_t *bit_no) {
  if(bit_no == NULL) return 1;

  *bit_no = BIT(kbd_hook_id);
  
  if (sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_hook_id)!= 0) return 1;
  
  return 0;
}

int (kbd_unsubscribe_int)() {
  if (sys_irqrmpolicy(&kbd_hook_id)!= 0)return 1;
  
  return 0; 
}
