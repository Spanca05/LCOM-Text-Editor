#ifndef _LCOM_UTF8_READER_H_
#define _LCOM_UTF8_READER_H_

#include "../utils/result.h"
#include "character.h"
#include <stdint.h>
#include <stdio.h>

typedef struct {
    Character character;
    int       bytes_consumed;
} UTF8_DecodeResult;

// Decodes up to 4 UTF-8 bytes into a Character enum value
Result utf8_decode_character(const uint8_t *bytes, int available_bytes, UTF8_DecodeResult *result);

// Reads a UTF-8 file and returns an array of lines
Result read_utf8_file(const char *filename, Character ***lines, int *line_count, int **line_lengths);

// Writes
Result write_utf8_file(const char *filename, Character **lines, int line_count, int *line_lengths);

// Frees memory allocated by read_utf8_file
void free_file_lines(Character **lines, int line_count);

#endif // _LCOM_UTF8_READER_H_
