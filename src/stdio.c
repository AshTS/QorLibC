#include "stdio.h"


int getchar(void)
{
    return fgetc(stdin);
}


int fgetc(FILE* stream)
{
    char buf;
    if (fread(&buf, 1, 1, stream))
    {
        return buf;
    }
    else
    {
        return 4;
    }
}

char* gets(char* buffer)
{
    char c;

    char* ptr = buffer;

    while (1)
    {
        c = getchar();
        if (c == 4)
        {
            if (ptr == buffer)
            {
                return NULL;
            }
            else
            {
                *ptr = 0;
                return buffer;
            }
        }
        else if (c == '\n')
        {
            *ptr = 0;
            return buffer;
        }
        
        *ptr = c;
        ptr++;
    }
}

char* fgets(char* buffer, int n, FILE* stream)
{
    char c;
    char* ptr = buffer;

    while (n > 0)
    {
        c = fgetc(stream);

        if (c == 4)
        {
            if (ptr == buffer)
            {
                return NULL;
            }
            else
            {
                *ptr = 0;
                return buffer;
            }
        }
        else if (c == '\n')
        {
            *ptr = 0;
            return buffer;
        }
        
        *ptr = c;
        ptr++;
        n--;
    }
}