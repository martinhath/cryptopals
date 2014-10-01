#include "libcrypto.h"

#include <stdio.h>
#include <stdlib.h>

int main(){
    int i;
    char* b64;

    b64 = malloc(sizeof(char)*4);

    byteatobase64a("Man", 3, b64);

    printf("%s\n", b64);
}
