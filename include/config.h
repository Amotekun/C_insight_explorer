#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>

void load_env_file(const char *filename);

static inline const char *get_api_key()
{
    return getenv("OPEN_API_KEY") ? getenv("OPENAI_API_KEY") : "";
}

#endif // CONFIG_H