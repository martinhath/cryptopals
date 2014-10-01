#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int len, i;
    char *key, c;
    if (argc > 2)
    {
        fprintf(stderr, "%s", "Usage: repkey <KEY>.\nInput data is supplied through stdin.");
    }
    key = argv[1];

    len = strlen(key);

    i = 0;
    while ((c = getchar()) != EOF)
    {
        if(i>=len)
            i = 0;
        putchar(c^key[i++]);
    }
}


