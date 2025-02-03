#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interactive_mode.h"
#include "openai_client.h"

void interactive_mode(const char *input)
{
    printf("User Input: %s\n", input);
    char *response = get_explanation(input);
    if (response)
    {
        printf("\nAI Explanation:\n%s\n", response);
        free(response);
    }
    else
    {
        printf("\n[Error] No response generated. \n");
    }
}