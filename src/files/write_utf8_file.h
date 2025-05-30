#ifndef WRITE_UTF8_FILE_H
#define WRITE_UTF8_FILE_H

#include "../model/line.h"
#include "../utils/result.h"

/**
 * @brief Writes the content of the buffer to a UTF-8 encoded file.
 *
 * This function writes the lines stored in the buffer to the specified file
 * in UTF-8 encoding. Each line is terminated with a newline character, except
 * the last line.
 *
 * @param filename Path to the output file.
 * @return 0 on success, -1 on failure.
 */
Result write_utf8_file(const char *filename);

#endif // WRITE_UTF8_FILE_H
