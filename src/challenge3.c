#include <stdio.h>
#include <stdlib.h>

#include "libcrypto.h"

#define BUFFER_SIZE 2048

void print_bytes(char* string){
    while(*string != 0)
        printf("%02.x ", *string++);
    printf("\n");
}

int main()
{
    char input[2048], c;
    unsigned char *bytes, key, *k;
    int i;

    i = 0;
    while ((c = getchar()) != EOF)
    {
        input[i++] = c;
    }
    input[i--] = 0;

    i = (i + 1) / 2;
    bytes = malloc(sizeof(unsigned char) * i);
    str_to_bytes(input, bytes, i);

    key = break_singlechar_xor(bytes, i);
    k = malloc(sizeof(char)+1);
    k[0] = key;
    k[1] = 0;
    decrypt_repeat_xor(bytes, k, i);
    printf("\nPrinting bytes:\n");
    print_bytes(bytes);
    printf("\nPrinting clear text\n");
    printf("%s\n", bytes);
    return 0;
}

