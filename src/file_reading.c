#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_reader.h"

char *read_file(const char *file_path)
{
    FILE *file = fopen(file_path, 'r');
    if (!file)
    {
        printf("Error opening file: %s\n", file_path);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *content = malloc(file_size + 1);
    if (!content)
    {
        printf("Memory allocation failed for file: %s\n", file_path);
        fclose(file);
        return NULL;
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0';
    fclose(file);

    return content;
}