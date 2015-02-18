#include "libhcrypto.h"

#include <stdlib.h>
#include <stdio.h>

#include <openssl/evp.h>

#define BUFFER_SIZE 4096

size_t read_input(char*, size_t);

static const char *KEY = "YELLOW SUBMARINE";

int main(){
    char input[BUFFER_SIZE];

    size_t len = read_input(input, BUFFER_SIZE);
    if (len == BUFFER_SIZE){
        fprintf(stderr, "Error: Whole file was not read.\n");
        exit(27); // EFBIG - File too large
    }

    byte *bytes = calloc(len, 1);
    len = base64tobstring(input, len, bytes);

    EVP_CIPHER_CTX ctx;

    EVP_CIPHER_CTX_init(&ctx);


}

size_t read_input(char *input, size_t n)
{
    char c;
    size_t i = 0;
    while (i < n && (c = (char) getchar()) != EOF)
        input[i++] = c;
    input[i-1] = '\0';
    return i;
}
