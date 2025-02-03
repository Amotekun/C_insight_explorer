#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <file_scanner.h>
#include <file_reader.h>
#include <openai_client.h>

void process_files()
{
    char directory[256];
    printf("Enter the directory to scan: ");
    scanf("%255s", directory);
    scan_directory(directory);

    char file_path[256];
    printf("Enter file path to explain: ");
    scanf("%255s", file_path);

    char *content = read_file(file_path);
    if (content)
    {
        char *response = get_explanation(content);
        printf("\nAI Explanation: \n%s\n", response);
        free(response);
        free(content);
    }
}