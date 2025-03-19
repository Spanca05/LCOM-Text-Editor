#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>

extern int counter;
extern int hook_id;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  uint8_t timer_conf;

  if(timer_get_conf(timer, &timer_conf) != OK) return 1;

  return timer_display_conf(timer, timer_conf, field);
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  if(timer_set_frequency(timer, freq) != OK) return 1;
  return 0;
}

int(timer_test_int)(uint8_t time) {
  int ipc_sta, r;
  message msg;
  uint8_t bit_no;
  int irq_set;

  if(timer_subscribe_int(&bit_no) != OK) return 1;

  irq_set = bit_no;

  counter = 0;

  while(counter < time * 60) {
    if((r = driver_receive(ANY, &msg, &ipc_sta)) != OK) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if(is_ipc_notify(ipc_sta)) {
      if(_ENDPOINT_P(msg.m_source) == HARDWARE) {
        if(msg.m_notify.interrupts & irq_set) {
          timer_int_handler();

          if(counter % 60 == 0) {
            timer_print_elapsed_time();
          }
        }
      }
    }
  }

  if(timer_unsubscribe_int() != OK) return 1;
  
  return 0;
}
