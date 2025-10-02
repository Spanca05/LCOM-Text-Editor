#include "utf8_reader.h"
#include <stdlib.h>
#include <string.h>

// Helper function to convert UTF-8 bytes to a Unicode codepoint
static uint32_t decode_utf8_codepoint(const uint8_t *bytes, int available_bytes, int *bytes_consumed) {
    if (available_bytes < 1) {
        *bytes_consumed = 0;
        return 0;
    }

    uint8_t first = bytes[0];

    // 1-byte sequence (ASCII)
    if ((first & 0x80) == 0) {
        *bytes_consumed = 1;
        return first;
    }

    // 2-byte sequence
    if ((first & 0xE0) == 0xC0) {
        if (available_bytes < 2) {
            *bytes_consumed = 0;
            return 0;
        }
        *bytes_consumed = 2;
        return ((uint32_t)(first & 0x1F) << 6) | (bytes[1] & 0x3F);
    }

    // 3-byte sequence
    if ((first & 0xF0) == 0xE0) {
        if (available_bytes < 3) {
            *bytes_consumed = 0;
            return 0;
        }
        *bytes_consumed = 3;
        return ((first & 0x0F) << 12) | ((bytes[1] & 0x3F) << 6) | (bytes[2] & 0x3F);
    }

    // 4-byte sequence
    if ((first & 0xF8) == 0xF0) {
        if (available_bytes < 4) {
            *bytes_consumed = 0;
            return 0;
        }
        *bytes_consumed = 4;
        return ((first & 0x07) << 18) | ((bytes[1] & 0x3F) << 12) | ((bytes[2] & 0x3F) << 6) | (bytes[3] & 0x3F);
    }

    // Invalid UTF-8
    *bytes_consumed = 1;
    return 0;
}

// Convert a Unicode codepoint to Character enum using character_to_char_map
static Character utf8_codepoint_to_character(uint32_t codepoint) {
    // Convert the codepoint back to UTF-8 bytes
    char utf8_bytes[5] = { 0 };
    if (codepoint < 0x80) {
        utf8_bytes[0] = (char)codepoint;
    } else if (codepoint < 0x800) {
        utf8_bytes[0] = 0xC0 | (codepoint >> 6);
        utf8_bytes[1] = 0x80 | (codepoint & 0x3F);
    } else if (codepoint < 0x10000) {
        utf8_bytes[0] = 0xE0 | (codepoint >> 12);
        utf8_bytes[1] = 0x80 | ((codepoint >> 6) & 0x3F);
        utf8_bytes[2] = 0x80 | (codepoint & 0x3F);
    } else {
        utf8_bytes[0] = 0xF0 | (codepoint >> 18);
        utf8_bytes[1] = 0x80 | ((codepoint >> 12) & 0x3F);
        utf8_bytes[2] = 0x80 | ((codepoint >> 6) & 0x3F);
        utf8_bytes[3] = 0x80 | (codepoint & 0x3F);
    }

    // Now search through all Character enum values to find a match
    for (Character ch = CHAR_NONE; ch <= CHAR_U_UMLAUT; ch++) { // Changed from 256 to CHAR_U_UMLAUT
        const char *char_utf8 = character_to_utf8(ch);
        if (strcmp(char_utf8, utf8_bytes) == 0) { return ch; }
    }

    return CHAR_NONE;
}

Result utf8_decode_character(const uint8_t *bytes, int available_bytes, UTF8_DecodeResult *result) {
    if (bytes == NULL || result == NULL) return RES_INVALID_ARGUMENT;
    if (available_bytes <= 0) return RES_INVALID_ARGUMENT;

    int      bytes_consumed;
    uint32_t codepoint = decode_utf8_codepoint(bytes, available_bytes, &bytes_consumed);

    if (bytes_consumed == 0) return RES_NOT_READY; // Need more bytes

    result->character      = utf8_codepoint_to_character(codepoint);
    result->bytes_consumed = bytes_consumed;

    return RES_OK;
}

Result read_utf8_file(const char *filename, Character ***lines, int *line_count, int **line_lengths) {
    if (filename == NULL || lines == NULL || line_count == NULL || line_lengths == NULL) return RES_INVALID_ARGUMENT;


    FILE *file = fopen(filename, "rb");
    if (file == NULL) return RES_IO_ERROR;

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size <= 0) {
        fclose(file);
        return RES_IO_ERROR;
    }

    // Read entire file into buffer
    uint8_t *buffer = malloc(file_size);
    if (buffer == NULL) {
        fclose(file);
        return RES_MEMORY_ERROR;
    }

    if (fread(buffer, 1, file_size, file) != (size_t)file_size) {
        free(buffer);
        fclose(file);
        return RES_IO_ERROR;
    }
    fclose(file);

    // Count lines
    int num_lines = 1; // At least one line
    for (long i = 0; i < file_size; i++)
        if (buffer[i] == '\n') num_lines++;


    // Allocate arrays
    Character **file_lines = malloc(num_lines * sizeof(Character *));
    int        *lengths    = malloc(num_lines * sizeof(int));
    if (file_lines == NULL || lengths == NULL) {
        free(buffer);
        free(file_lines);
        free(lengths);
        return RES_MEMORY_ERROR;
    }

    // Initialize arrays
    for (int i = 0; i < num_lines; i++) {
        file_lines[i] = NULL;
        lengths[i]    = 0;
    }

    // Count characters per line
    int  current_line = 0;
    long byte_pos     = 0;

    while (byte_pos < file_size) {
        UTF8_DecodeResult decode_result;
        int               remaining_bytes = file_size - byte_pos;

        Result res = utf8_decode_character(&buffer[byte_pos], remaining_bytes, &decode_result);
        if (res != RES_OK) {
            // Skip invalid byte
            byte_pos++;
            continue;
        }

        if (decode_result.character == CHAR_NEWLINE) {
            current_line++;
        } else {
            lengths[current_line]++;
        }

        byte_pos += decode_result.bytes_consumed;
    }

    // Allocate character arrays for each line
    for (int i = 0; i < num_lines; i++) {
        if (lengths[i] > 0) {
            file_lines[i] = malloc(lengths[i] * sizeof(Character));
            if (file_lines[i] == NULL) {
                // Cleanup on failure
                for (int j = 0; j < i; j++) { free(file_lines[j]); }
                free(file_lines);
                free(lengths);
                free(buffer);
                return RES_MEMORY_ERROR;
            }
        }
    }

    // Fill the character arrays
    current_line = 0;
    int char_pos = 0;
    byte_pos     = 0;

    while (byte_pos < file_size) {
        UTF8_DecodeResult decode_result;
        int               remaining_bytes = file_size - byte_pos;

        Result res = utf8_decode_character(&buffer[byte_pos], remaining_bytes, &decode_result);
        if (res != RES_OK) {
            byte_pos++;
            continue;
        }

        if (decode_result.character == CHAR_NEWLINE) {
            current_line++;
            char_pos = 0;
        } else {
            if (current_line < num_lines && char_pos < lengths[current_line]) {
                file_lines[current_line][char_pos] = decode_result.character;
                char_pos++;
            }
        }

        byte_pos += decode_result.bytes_consumed;
    }

    free(buffer);

    *lines        = file_lines;
    *line_count   = num_lines;
    *line_lengths = lengths;

    return RES_OK;
}

void free_file_lines(Character **lines, int line_count) {
    if (lines == NULL) return;

    for (int i = 0; i < line_count; i++) { free(lines[i]); }
    free(lines);
}
