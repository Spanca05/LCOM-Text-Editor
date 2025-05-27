#include "../utils/result.h"
#include "../utils/utils.h"
#include "i8254.h"
#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>

int timer_hook_id = 0;

Result(res_timer_subscribe_int)(uint8_t *bit_no) {
    if (bit_no == NULL) return RES_INVALID_ARGUMENT;

    *bit_no = BIT(timer_hook_id);
    if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id) != RES_OK) return RES_PERMISSION_ERROR;

    return RES_OK;
}

Result(res_timer_unsubscribe_int)() {
    if (sys_irqrmpolicy(&timer_hook_id) != RES_OK) return RES_PERMISSION_ERROR;
    return RES_OK;
}

Result(res_timer_get_conf)(uint8_t timer, uint8_t *st) {
    if (timer > 2) return RES_INVALID_ARGUMENT;

    uint8_t read_back_cmd = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
    if (sys_outb(TIMER_CTRL, read_back_cmd) != RES_OK) return RES_IO_ERROR;

    if (res_util_sys_inb(TIMER_0 + timer, st) != RES_OK) return RES_IO_ERROR;

    return RES_OK;
}
