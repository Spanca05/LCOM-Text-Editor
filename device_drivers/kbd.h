#ifndef _LCOM_KBD_H_
#define _LCOM_KBD_H_

#include "../utils/result.h"
#include <lcom/lcf.h>

void(kbc_ih)();

Result(kbd_subscribe_int)(uint8_t *bit_no);
Result(kbd_unsubscribe_int)();
Result(kbc_restore)();

#endif
