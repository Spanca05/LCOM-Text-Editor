#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../model/buffer.h"
#include "write_utf8_file.h"

Result(write_utf8_file)(const char *filename) {
    printf("her");
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return RES_IO_ERROR;
    }


    // Write each line from text_buffer to the file
    for (size_t i = 0; i < text_buffer.length; i++) {
        Line *line = &text_buffer.lines[i];
        for (size_t j = 0; j < line->length; j++) {
            const char *utf8_str = character_to_utf8(line->data[j]);
            if (utf8_str != NULL && utf8_str[0] != '\0')
                if (fputs(utf8_str, file) == EOF) {
                    perror("Failed to write to file");
                    fclose(file);
                    return RES_IO_ERROR;
                }
        }

        if (fputc('\n', file) == EOF) {
            perror("Failed to write newline to file");
            fclose(file);
            return RES_IO_ERROR;
        }
    }

    fclose(file);
    return RES_OK;
}
