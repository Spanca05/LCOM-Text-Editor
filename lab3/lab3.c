#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"
#include "kbd.h"

extern int kbd_hook_id;
extern uint16_t scancode;
extern int sys_inb_count;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  int ipc_sta;
  message msg;
  uint8_t bit_no, MSB, LSB;
  //int irq_set;

  // Subscribe the KBC interrupts
  if(kbd_subscribe_int(&bit_no) != OK) {
    printf("Error subscribing keyboard interrupts\n");
    return 1;
  }
  printf("Subscrição do teclado feita com sucesso! IRQ: %d\n", bit_no);

  //irq_set = bit_no;

  //printf("IRQ_SET configurado corretamente? irq_set = 0x%x\n", irq_set);


  // Loop that ends when ESC key is pressed
  while(scancode != BREAK_ESC) {
    
    printf("inside");

    if((driver_receive(ANY, &msg, &ipc_sta)) != OK) {
      printf("driver_receive failed");
      continue;
    }
    

    if(is_ipc_notify(ipc_sta)) {
      if(_ENDPOINT_P(msg.m_source) == HARDWARE) {
        if(msg.m_notify.interrupts & bit_no) {
          kbc_ih();

          if(util_get_MSB(scancode, &MSB) != OK) return 1;
          if(util_get_LSB(scancode, &LSB) != OK) return 1;
          
          //Check if scancode is one byte long
          if(MSB == 0x00) {
            uint8_t scancode_arr[1] = {LSB};

            if((LSB & BIT(7)) == 0) {
              if(kbd_print_scancode(true, 1, scancode_arr) != OK) return 1;
            }
            else {
              if(kbd_print_scancode(false, 1, scancode_arr) != OK) return 1;
            }
          }
          else {
            uint8_t scancode_arr[2] = {MSB, LSB};
            
            // Scancode is two bytes long
            if((scancode & BIT(15)) == 0) {
              if(kbd_print_scancode(true, 2, scancode_arr) != OK) return 1;
            }
            else {
              if(kbd_print_scancode(false, 2, scancode_arr) != OK) return 1;
            }
          }
        }
      }
    }
  }

  // Unsubscribe the KBC interrupts
  if(kbd_unsubscribe_int() != OK) {
    printf("Error unsubscribing keyboard interrupts\n");
    return 1;
  }

  kbd_print_no_sysinb(sys_inb_count);

  printf("Exiting program...\n");

  return 0;
}

int(kbd_test_poll)() {
  uint8_t status, byte, scancode = 0x00;
  uint8_t scancode_arr[2];
  bool is_two_byte = false;

  while(scancode != BREAK_ESC) {
    //1. Read status register 0x64
    if(util_sys_inb(KBC_STATUS_REG, &status) != OK) continue;

    //2. Check if there is data to be read from the output register (bit 0)
    if(status & OUTPUT_BUFFER_FULL) {
      //3. Check if there is a parity or timeout error
      if(status & (PARITY_ERROR | TIMEOUT_ERROR)) continue;

      //4. Read byte from output buffer (0x60)
      if(util_sys_inb(KBC_OUT_BUF, &byte) != OK) continue;

      //5. Check if scancode is two bytes long
      if(byte == 0xE0) {
        is_two_byte = true;
        continue;
      }

      if(is_two_byte) {
        scancode_arr[0] = 0xE0;
        scancode_arr[1] = byte;
        scancode = (0xE0 << 8) | byte;
        is_two_byte = false;

        kbd_print_scancode(!(byte & BIT(7)), 2, scancode_arr);
      }
      else {
        scancode_arr[0] = byte;
        scancode = byte;

        kbd_print_scancode(!(byte & BIT(7)), 1, scancode_arr);
      }
    } 
  }
  
  //6. Reactivate keyboard interrupts
  if(kbc_restore() != OK) return 1;
  
  //7. Print number of sys_inb() calls
  if(kbd_print_no_sysinb(sys_inb_count) != OK) return 1;

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
