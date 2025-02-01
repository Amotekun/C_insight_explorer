#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "openai_client.h"

typedef struct MemoryStruct
{
    char *memory;
    size_t size;
} MemoryStruct;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL)
    {
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;

    char *get_explanation(const char *prompt)
    {
        CURL *curl;
        Curlcode res;
        MemoryStruct chunk;
        chunk.memory = malloc(1);
        chunk.size = 0;

        const char *api_key = get_api_key();

        if (api_key == NULL || strlen(api_key) == 0)
        {
            fprintf(stderr, "Error: API is missing! Ensure it is set in the enviroment variables.\n");
            return NULL;
        }

        curl_global_init(CURL_GLOBAL_ALL); // sets up global networking & SSL (only call once)
        curl = curl_easy_init();           // Creates per-request session handle.

        if (curl)
        {
            struct curl_s_list *headers = NULL; // pointer to store HTTP headers

            // this is also used to create and manage linked lists of HTTP headers for cURL requests.
            headers = curl_slist_append(headers, "Content-Type: application/json");
            char auth_header[256];
        }
    }
}