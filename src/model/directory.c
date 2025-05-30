#include "directory.h"

Result(render_directory)(char *path, char *filenames[], int *num_files) {
    if (path == NULL ^ filenames == NULL ^ num_files == NULL) return RES_INVALID_ARGUMENT;

    DIR *directory;
    directory = opendir(path);

    if (directory == NULL) return RES_ERROR;

    struct dirent *file;
    (*num_files) = 0;

    while ((file = readdir(directory)) != NULL) {
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) continue;
        filenames[*num_files] = strdup(file->d_name);
        (*num_files)++;
    }

    closedir(directory);
    return RES_OK;
}

Result(insert_file)(char *path, char *file_name, char *content) {
    if (path == NULL || file_name == NULL || content == NULL) return RES_INVALID_ARGUMENT;
    
    size_t length = strlen(path) + 1 + strlen(file_name) + 1;
    char *full_path = malloc(length);
    if (full_path == NULL){printf("FULLPATH\n") ;return RES_ERROR;}
    
    strcpy(full_path, path);
    strcat(full_path, "/");
    strcat(full_path, file_name);
    
    FILE *file = fopen(full_path, "w");
    if (file == NULL) {perror("fopen failed\n");free(full_path); return RES_ERROR;}
    
    if (fprintf(file,"%s",content) == EOF) {
        printf("fputs failed\n");
    }

    fclose(file);
    free(full_path);

    return RES_OK;
}

Result(delete_file)(char *path, char *file_name) {
    if (path == NULL || file_name == NULL) return RES_INVALID_ARGUMENT;

    size_t length = strlen(path) + 2 + strlen(file_name);
    char *full_path = malloc(length);

    strcpy(full_path, path);
    strcat(full_path, "/");
    strcat(full_path, file_name);

    if (remove(full_path) != 0) return RES_ERROR;

    free(full_path);
    return RES_OK;
}

Result(create_menu)(char* buffer, char* filenames[], int *num_files) {
    if (buffer == NULL || filenames == NULL || num_files == NULL) return RES_INVALID_ARGUMENT;

    strcat(buffer, "Files: \n");
    if (*num_files == 0)
    {
        strcat(buffer, "\tThere are no files available.");
    }
    else if (*num_files > 0)
    {
        for (int i = 0; i < *num_files; i++) {
            char line[128];
            snprintf(line, sizeof(line), "\t%d) %s\n", i + 1, filenames[i]);
            strcat(buffer, line);
        }
    }
    
    strcat(buffer, "Create a new one!");

    return RES_OK;
}