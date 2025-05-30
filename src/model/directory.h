#include "../utils/result.h"
#include <sys/file.h>
#include <stdio.h>
#include <dirent.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

Result(render_directory)(char *path, char* filenames[], int *num_files);

Result(insert_file)(char *path, char *file_name, char *content);
Result(delete_file)(char *path, char *file_name);

Result(create_menu)(char *buffer, char* filenames[], int *num_files);