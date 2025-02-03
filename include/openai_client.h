/* file_reader.h - Header for OpenAI interaction */
#ifndef OPENAI_CLIENT_H
#define OPENAI_CLIENT_H
#include "config.h"
#define API_URL "https://api.openai.com/v1/chat/completions"

char *get_explanation(const char *prompt);

#endif // OPENAI_CLIENT_H