#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <file_scanner.h>

void scan_directory(const char *directory)
{
    struct dirent *entry;
    DIR *dp = opendir(directory);

    if (dp == NULL)
    {
        printf("Error opening directory: %s\n", directory);
        return;
    }

    printf("Scanning directory: %s\n", directory);

    entry = readdir(dp);

    while (entry != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            printf("File not found: %s\n", entry->d_name);
        }
    }
    closedir(dp);
}