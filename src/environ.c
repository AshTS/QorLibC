#include "stdlib.h"

#include "string.h"

const char** environ;

void _store_envp(int argc, char** argv, const char** envp)
{
    environ = envp;
}

char* getenv(const char* name)
{
    int name_length = strlen(name);

    char* name_and_equals = malloc(name_length + 2);
    strcpy(name_and_equals, name);
    strcat(name_and_equals, "=");

    int compare_length = name_length + 1;

    for (int i = 0; environ[i] != NULL; i++)
    {
        if (memcmp(name_and_equals, environ[i], compare_length) == 0)
        {
            free(name_and_equals);
            return (char*)environ[i] + compare_length;
        }
    }

    free(name_and_equals);
    return NULL;
}