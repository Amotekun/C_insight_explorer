#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "openai_client.h"
#include "config.h"

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
}

char *get_explanation(const char *prompt)
{
    CURL *curl;
    CURLcode res;
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
        struct curl_slist *headers = NULL; // pointer to store HTTP headers

        // this is also used to create and manage linked lists of HTTP headers for cURL requests.
        headers = curl_slist_append(headers, "Content-Type: application/json");
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", api_key);
        headers = curl_slist_append(headers, auth_header);

        char post_fields[512];
        snprintf(post_fields, sizeof(post_fields), "{\"model\": \"gpt-4\", \"messages\": [{\"role\": \"system\", \"content\": \"You are a knowledgeable AI that explains code.\"}, {\"role\": \"user\", \"content\": \"%s\"}]}", prompt);

        printf("DEBUG: API URL being used: %s\n", API_URL);
        curl_easy_setopt(curl, CURLOPT_URL, API_URL);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();
    return chunk.memory;
}