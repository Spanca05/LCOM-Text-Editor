#ifndef _LCOM_UTF8_READER_H_
#define _LCOM_UTF8_READER_H_

#include "../model/character.h"
#include "../utils/result.h"
#include <stdint.h>
#include <stdio.h>

/**
 * @struct UTF8_DecodeResult
 * @brief Represents the result of decoding a UTF-8 sequence.
 *
 * This structure contains the decoded character and the number of bytes
 * consumed during the decoding process.
 */
typedef struct {
    Character character;      /** The decoded character as a Character enum. */
    int       bytes_consumed; /** The number of bytes consumed from the input. */
} UTF8_DecodeResult;

/**
 * @brief Decodes a UTF-8 sequence into a Character enum value.
 *
 * This function attempts to decode up to 4 bytes of a UTF-8 sequence into
 * a Character enum value. It also provides the number of bytes consumed
 * during the decoding process.
 *
 * @param bytes Pointer to the UTF-8 byte sequence.
 * @param available_bytes Number of bytes available in the input buffer.
 * @param result Pointer to a UTF8_DecodeResult structure to store the result.
 * @return Result code indicating success or failure.
 *         - RES_OK: Decoding was successful.
 *         - RES_INVALID_ARGUMENT: Invalid input arguments.
 *         - RES_NOT_READY: More bytes are needed to complete decoding.
 */
Result utf8_decode_character(const uint8_t *bytes, int available_bytes, UTF8_DecodeResult *result);

/**
 * @brief Reads a UTF-8 encoded file and parses it into lines of characters.
 *
 * This function reads a UTF-8 encoded file and converts its content into
 * an array of lines, where each line is represented as an array of Character
 * enums. It also provides the number of lines and the length of each line.
 *
 * @param filename Path to the UTF-8 encoded file.
 * @param lines Pointer to store the array of lines (allocated dynamically).
 * @param line_count Pointer to store the number of lines.
 * @param line_lengths Pointer to store the lengths of each line.
 * @return Result code indicating success or failure.
 *         - RES_OK: File was read and parsed successfully.
 *         - RES_INVALID_ARGUMENT: Invalid input arguments.
 *         - RES_IO_ERROR: File I/O error occurred.
 *         - RES_MEMORY_ERROR: Memory allocation failed.
 */
Result read_utf8_file(const char *filename, Character ***lines, int *line_count, int **line_lengths);

/**
 * @brief Writes an array of lines to a UTF-8 encoded file.
 *
 * This function writes the provided lines of characters to a file in UTF-8
 * encoding. Each line is terminated with a newline character, except the last line.
 *
 * @param filename Path to the output file.
 * @param lines Array of lines to write, where each line is an array of Character enums.
 * @param line_count Number of lines to write.
 * @param line_lengths Array containing the length of each line.
 * @return Result code indicating success or failure.
 *         - RES_OK: File was written successfully.
 *         - RES_INVALID_ARGUMENT: Invalid input arguments.
 *         - RES_IO_ERROR: File I/O error occurred.
 */
Result write_utf8_file(const char *filename, Character **lines, int line_count, int *line_lengths);

/**
 * @brief Frees memory allocated by read_utf8_file.
 *
 * This function releases the memory allocated for the lines and their contents
 * by the read_utf8_file function.
 *
 * @param lines Array of lines to free.
 * @param line_count Number of lines in the array.
 */
void free_file_lines(Character **lines, int line_count);

#endif // _LCOM_UTF8_READER_H_
