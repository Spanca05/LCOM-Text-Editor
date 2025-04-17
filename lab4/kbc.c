#include <lcom/lcf.h>

#include "kbc.h"
#include "i8042.h"

int (read_KBC_status)(uint8_t *status) {
    // Read status register
    return util_sys_inb(0x64, &status);
}

int(read_KBC_output)(uint8_t port, uint8_t *output, uint8_t mouse) {
    uint8_t status;
    uint8_t attempts = 10;

    while(attempts) {
        if(read_KBC_status(&status) != OK) return 1;

        // If output buffer empty, wait and retry
        if(!(status & BIT(0))) {
          tickdelay(micros_to_ticks(20000));
          attempts--;
          continue;
        }

        //! Tem que ler o byte antes de verificar os erros , porque mesmo que tenha erros, é preciso ler o byte, e se fosse depois de verificar se tinha erros, não iria descartar o byte
        // Read byte in the output buffer
        if(util_sys_inb(port, output) != OK) return 1;

        // Check if there was some communication error
        if(status & BIT(7) || status & BIT(6)) return 1;

        // Check if there is no data to be read
        if(!(status & BIT(0))) return 1;

        // If data is expected to come from mouse and it doesn't
        if(mouse && !(status & BIT(5))) return 1;

        // If data is expected to come from keyboard and it doesn't
        if(!mouse && (status & BIT(5))) return 1;

        // If successful, return
        return 0;
    }
    // If after n attempts, not successfull, return with error
    return 1;
}

int(write_KBC_command)(uint8_t port, uint8_t commandByte) {
    uint8_t status;
    uint8_t attempts = 10;

    while(attempts) {

        // Read status register
        if(read_KBC_status(&status) != OK) return 1;

        // Check if input buffer full
        if(status & BIT(1)) {
            tickdelay(micros_to_ticks(20000));
            attempts--;
            continue;
        }

        //! Porquê port? Não é sempre o mesmo register? 
        //* Pode ser 0x64 para passar comandos para o KBC, ou 0x60 para passar argumentos
        if(sys_outb(port, commandByte) != OK) return 1;

        return 0;
    }
    return 1;
}