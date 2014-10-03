#include "libcrypto.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, k;
    char *b64, *bytestr;

    b64 = malloc(sizeof(char) * 6);
    bytestr = malloc(sizeof(char) * 6);

    byteatobase64a("Manmax", 6, b64);

    base64tobstring(b64, 6, bytestr);
    bytestr[6] = 0;

    printf("%s\n", bytestr);
}


