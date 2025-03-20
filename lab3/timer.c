#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int counter = 0;
int timer_hook_id = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if( freq > TIMER_FREQ) return 1;

  uint16_t counter = TIMER_FREQ / freq;
  uint8_t timer_conf;
  
  if(timer_get_conf(timer, &timer_conf) != OK) return 1;
  
  uint8_t command = 0;

  if(timer == 0) command |= TIMER_SEL0;
  if(timer == 1) command |= TIMER_SEL1;
  if(timer == 2) command |= TIMER_SEL2;

  command |= TIMER_LSB_MSB;

  command |= (timer_conf & (BIT(3) | BIT(2) | BIT(1)));

  command |= (timer_conf & TIMER_BCD);

  if(sys_outb(TIMER_CTRL, command) != OK) return 1;

  uint8_t LSB = counter & 0xFF;
  uint8_t MSB = (counter >> 8) & 0xFF;

  if(sys_outb(TIMER_0 + timer, LSB) != OK) return 1;
  if(sys_outb(TIMER_0 + timer, MSB) != OK) return 1;

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  if(bit_no == NULL) return 1;
  *bit_no = BIT(timer_hook_id);
  if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id) != OK) return 1;
  return 0;
}

int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&timer_hook_id) != OK) return 1;
  return 0;
}

void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (timer > 2) return 1;

  uint8_t read_back_cmd = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  sys_outb(TIMER_CTRL, read_back_cmd);  // Escrever o read-back command para o Control Register

  return util_sys_inb(TIMER_0 + timer, st);
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val val; // Criamos uma variável da união para armazenar o valor interpretado.

  switch (field)  // Verificamos qual campo do byte de estado queremos extrair.
  {
  case tsf_all: // Se for tsf_all, apenas armazenamos o byte inteiro.
    val.byte = st;
    break;

  case tsf_initial: // Se for tsf_initial, extraímos o modo de inicialização.
    val.in_mode = (st & TIMER_LSB_MSB) >> 4;  // Desativa todos os bits menos o 4 e o 5, e depois faz right shifts para os alinhar
    break;

  case tsf_mode: // Se for tsf_mode, extraímos os bits 3, 2 e 1 que determinam o modo do temporizador.
    val.count_mode = (st & (BIT(3) | BIT(2) | BIT(1))) >> 1; // Aplicamos uma máscara para isolar os bits do modo e fazemos shift para normalizar.

    // No i8254, os modos 6 e 7 são equivalentes a 2 e 3, então corrigimos isso.
    if (val.count_mode == 6) val.count_mode = 2;
    if (val.count_mode == 7) val.count_mode = 3;
    break;

  case tsf_base: // Se for tsf_base, verificamos se o contador está em BCD ou binário.
    val.bcd = st & TIMER_BCD; // O bit 0 indica se está em BCD (1) ou binário (0).
    break;

  default: // Se o campo não for nenhum dos esperados, retornamos erro.
    return 1;
  }
  
  // Chama a função timer_print_config() para exibir a configuração interpretada.
  return timer_print_config(timer, field, val);
}
