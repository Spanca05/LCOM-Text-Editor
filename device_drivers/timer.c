#include "../utils/result.h"
#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

// Global variables for timer interrupt handling
int count         = 0;
int timer_hook_id = 0;

/**
 * @brief Sets the frequency of the specified timer.
 * @param timer The timer to configure (0, 1, or 2).
 * @param freq The desired frequency.
 * @return Result indicating success or specific error.
 */
Result(timer_set_frequency)(uint8_t timer, uint32_t freq) {
    if (freq > TIMER_FREQ) return RES_INVALID_ARGUMENT;

    uint16_t counter = TIMER_FREQ / freq;
    uint8_t  timer_conf;

    if (timer_get_conf(timer, &timer_conf) != RES_OK) return RES_IO_ERROR;

    uint8_t command = 0;

    if (timer == 0) command |= TIMER_SEL0;
    if (timer == 1) command |= TIMER_SEL1;
    if (timer == 2) command |= TIMER_SEL2;

    command |= TIMER_LSB_MSB;

    command |= (timer_conf & (BIT(3) | BIT(2) | BIT(1)));

    command |= (timer_conf & TIMER_BCD);

    if (sys_outb(TIMER_CTRL, command) != RES_OK) return RES_IO_ERROR;

    uint8_t LSB = counter & 0xFF;
    uint8_t MSB = (counter >> 8) & 0xFF;

    if (sys_outb(TIMER_0 + timer, LSB) != RES_OK) return RES_IO_ERROR;
    if (sys_outb(TIMER_0 + timer, MSB) != RES_OK) return RES_IO_ERROR;

    return RES_OK;
}

/**
 * @brief Subscribes to timer interrupts.
 * @param bit_no Pointer to store the bit number of the interrupt.
 * @return Result indicating success or specific error.
 */
Result(timer_subscribe_int)(uint8_t *bit_no) {
    if (bit_no == NULL) return RES_INVALID_ARGUMENT;

    *bit_no = BIT(timer_hook_id);

    if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id) != RES_OK) return RES_PERMISSION_ERROR;

    return RES_OK;
}

/**
 * @brief Unsubscribes from timer interrupts.
 * @return Result indicating success or specific error.
 */
Result(timer_unsubscribe_int)() {
    if (sys_irqrmpolicy(&timer_hook_id) != RES_OK) return RES_PERMISSION_ERROR;
    return RES_OK;
}

/**
 * @brief Timer interrupt handler. Increments the global count variable.
 */
void(timer_int_handler)() { count++; }

/**
 * @brief Gets the configuration of the specified timer.
 * @param timer The timer to query (0, 1, or 2).
 * @param st Pointer to store the status byte.
 * @return Result indicating success or specific error.
 */
Result(timer_get_conf)(uint8_t timer, uint8_t *st) {
    if (timer > 2) return RES_INVALID_ARGUMENT;

    uint8_t read_back_cmd = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
    if (sys_outb(TIMER_CTRL, read_back_cmd) != RES_OK) return RES_IO_ERROR;

    if (util_sys_inb(TIMER_0 + timer, st) != RES_OK) return RES_IO_ERROR;

    return RES_OK;
}

/**
 * @brief Displays the configuration of the specified timer.
 * @param timer The timer to display.
 * @param st The status byte of the timer.
 * @param field The field to interpret and display.
 * @return Result indicating success or specific error.
 */
Result(timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
    union timer_status_field_val val;

    switch (field) {
    case tsf_all: val.byte = st; break;

    case tsf_initial: val.in_mode = (st & TIMER_LSB_MSB) >> 4; break;

    case tsf_mode:
        val.count_mode = (st & (BIT(3) | BIT(2) | BIT(1))) >> 1;
        if (val.count_mode == 6) val.count_mode = 2;
        if (val.count_mode == 7) val.count_mode = 3;
        break;

    case tsf_base: val.bcd = st & TIMER_BCD; break;

    default: return RES_INVALID_ARGUMENT;
    }

    if (timer_print_config(timer, field, val) != RES_OK) return RES_IO_ERROR;

    return RES_OK;
}
