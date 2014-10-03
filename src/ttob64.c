#include "libcrypto.h"

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 2048

int main()
{
    char input[BUFFER_SIZE], c;
    unsigned char *bytea, *b64a;
    int i, n, b64_size;

    i = 0;
    while ((c = getchar()) != EOF)
    {
        input[i++] = c;
    }
    input[i] = 0;

    bytea = malloc(sizeof(unsigned char)*(i+1)/2);
    i = str_to_bytes(input, bytea, i);
    
    b64_size = ((i+2)/3)*4;

    b64a = malloc(sizeof(unsigned char)*b64_size);

    byteatobase64a(bytea, i, b64a);
    printf("%s\n", b64a);
}

