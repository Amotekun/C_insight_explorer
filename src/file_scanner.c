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

    int file_count = 0;

    entry = readdir(dp);

    while ((entry = readdir(dp)))
    {
        if (entry->d_type == DT_REG)
        {
            printf("File found: %s\n", entry->d_name);
            file_count++;
        }

        if (file_count > 1000)
        {
            printf("Too many files, stopping...\n");
            break;
        }
    }
    closedir(dp);
    printf("Scan completed. Total files found: %d\n", file_count);
}