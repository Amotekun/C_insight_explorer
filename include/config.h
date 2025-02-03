#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>

void load_env_file(const char *filename);

const char *get_api_key();

#endif // CONFIG_H