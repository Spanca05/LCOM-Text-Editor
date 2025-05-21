#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the i8042 Keyboard Controller (KBC).
 */

#define KEYBOARD_IRQ 1          /**< @brief Keyboard IRQ line */
#define MOUSE_IRQ    12         /**< @brief Mouse IRQ line */

#define KBC_STATUS_REG     0x64 /**< @brief Status Register */
#define KBC_CMD_REG        0x64 /**< @brief Command Register (same as status register) */
#define KBC_WRITE_CMD_PORT 0x64 /**< @brief Write command to the controller */
#define KBC_WRITE_CMD_BYTE 0x60 /**< @brief Write command byte */
#define KBC_WRITE_BUF      0x60 /**< @brief Buffer to write to KBC */
#define KBC_OUT_BUF        0x60 /**< @brief Output Buffer */
#define KBC_READ_CMD_BYTE  0x20 /**< @brief Read command byte */

#define PARITY_ERROR       BIT(7)
#define TIMEOUT_ERROR      BIT(6)
#define INPUT_BUFFER_FULL  BIT(1)
#define OUTPUT_BUFFER_FULL BIT(0)

#define BREAK_ESC 0x81 /**< @brief Scancode for ESC break */

#define ACK   0xFA
#define NACK  0xFE
#define ERROR 0xFC

/**@}*/

#endif /* _LCOM_I8042_H_ */
