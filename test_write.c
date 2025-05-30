#include "src/model/utf8_reader.h"
#include "src/model/character.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    
    const char *input_filename = argv[1];
    const char *output_filename = argv[2];
    
    printf("Reading file: %s\n", input_filename);
    
    // Read the file
    Character **lines;
    int line_count;
    int *line_lengths;
    
    Result res = read_utf8_file(input_filename, &lines, &line_count, &line_lengths);
    if (res != RES_OK) {
        printf("Failed to read file '%s', error: %d\n", input_filename, res);
        return 1;
    }
    
    printf("Read %d lines successfully!\n", line_count);
    
    // Write the file back
    printf("Writing to file: %s\n", output_filename);
    res = write_utf8_file(output_filename, lines, line_count, line_lengths);
    if (res != RES_OK) {
        printf("Failed to write file '%s', error: %d\n", output_filename, res);
        free_file_lines(lines, line_count);
        free(line_lengths);
        return 1;
    }
    
    printf("File written successfully!\n");
    
    // Clean up
    free_file_lines(lines, line_count);
    free(line_lengths);
    
    return 0;
}