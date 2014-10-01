#include <stdio.h>
#include <stdlib.h>

#include "libcrypto.h"

#define BUFFER_SIZE 2048

int main()
{
    char input[2048], c;
    unsigned char *bytes, *xor_bytes, chr, key;
    int i, j, try_score, max_score, k;

    i = 0;
    while ((c = getchar()) != EOF)
    {
        input[i++] = c;
    }
    input[i] = 0;

    i = (i + 1) / 2;
    bytes = malloc(sizeof(unsigned char) * i);
    str_to_bytes(input, bytes, i);

    xor_bytes = malloc(sizeof(unsigned char) * i);
    key = 0;
    max_score = 0;
    for (chr = 0; chr != 255; chr++)
    {
        for (j = 0; j < i; j++)
        {
            xor_bytes[j] = bytes[j] ^ chr;
        }
        if ((try_score = rate_string(xor_bytes, i)) > max_score)
        {
            key = chr;
            max_score = try_score;
        }
    }
    for (j = 0; j < i; j++)
    {
        xor_bytes[j] = bytes[j] ^ key;
    }
    printf("Score: %d\t",  max_score);
    printf("Key: %d\t\t", key);
    printf("[%s]\n", xor_bytes);
}

int rate_string(unsigned char* str, size_t n)
{
    int i, score;
    score = 0;
    for (i = 0; i < n; i++)
    {
        switch (str[i])
        {
        case ' ':
        case 'a':
        case 'e':
        case 's':
            score += 5;
            break;
        case 'i':
        case 'c':
        case 'h':
            score += 2;
            break;
        }
    }
    return score;
}


