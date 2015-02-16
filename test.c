#include "src/libcrypto.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned char str[] = {0x1d, 0x42, 0x1f};
    char ord[4] = {};
    byteatobase64a(str, 4, ord);
    for (int i = 0; i < 4; i++){
        printf(".%c.", ord[i]);
    }
    printf("\n");
    printf("%s\n", ord);
}


