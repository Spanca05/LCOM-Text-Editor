#include "src/model/utf8_reader.h"
#include "src/model/character.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    const char *filename = argv[1];
    printf("Reading file: %s\n\n", filename);
    
    Character **lines;
    int line_count;
    int *line_lengths;
    
    Result res = read_utf8_file(filename, &lines, &line_count, &line_lengths);
    if (res != RES_OK) {
        printf("Failed to read file '%s', error: %d\n", filename, res);
        return 1;
    }
    
    printf("File '%s' read successfully! Found %d lines:\n\n", filename, line_count);
    
    for (int i = 0; i < line_count; i++) {
        printf("Line %d (%d characters):\n", i + 1, line_lengths[i]);
        
        if (line_lengths[i] == 0) {
            printf("  (empty line)\n");
        } else {
            printf("  Characters: ");
            for (int j = 0; j < line_lengths[i]; j++) {
                printf("%d ", lines[i][j]);
            }
            printf("\n");
            
            printf("  Content: \"");
            for (int j = 0; j < line_lengths[i]; j++) {
                printf("%s", character_to_utf8(lines[i][j]));
            }
            printf("\"\n");
        }
        printf("\n");
    }
    
    free_file_lines(lines, line_count);
    free(line_lengths);
    
    return 0;
}