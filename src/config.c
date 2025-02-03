#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

void load_env_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Failed to open .env file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        if (line[0] == '#' || line[0] == '\n')
        {
            continue;
        }

        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");

        if (key && value)
        {
            if (value[0] == '"' && value[strlen(value)] - 1 == '"')
            {
                value[strlen(value) - 1] = '\0';
                value++;
            }

            printf("Setting Env: %s = %s\n", key, value);
            setenv(key, value, 1);
        }
    }

    fclose(file);
}