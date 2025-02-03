#include <stdio.h>
#include <string.h>
#include "config.h"
#include "process_files.h"
#include "interactive_mode.h"

int main()
{
    printf("\nWelcome to the file Explorer & AI Code Explainer in C!\n");
    printf("Type 'file()' to scan a directory or ask a direct question. Type 'quit' to exit.\n\n");

    load_env_file(".env");

    char user_input[256];
    while (1)
    {
        printf("\nEnter your choice: ");
        fgets(user_input, sizeof(user_input), stdin);

        // Remove newline character from input
        user_input[strcspn(user_input, "\n")] = 0;

        if (strcmp(user_input, "file()") == 0)
        {
            process_files();
            break;
        }
        else if (strcmp(user_input, "quit()") == 0)
        {
            printf("\n[Exciting...]\n");
            break;
        }
        else
        {
            interactive_mode(user_input);
        }
    }

    return 0;
}