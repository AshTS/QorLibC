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
        return 404;
    }
}

char* gets(char* buffer)
{
    char c;

    char* ptr = buffer;

    while (1)
    {
        c = getchar();
        if (c == 404)
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

    while (n > 1)
    {
        c = fgetc(stream);

        if (c == 404)
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
            *ptr = c;
            *(ptr + 1) = 0; 
            return buffer;
        }
        
        *ptr = c;
        ptr++;
        n--;
    }

    *ptr = 0;
    return buffer;
}