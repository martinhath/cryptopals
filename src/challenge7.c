#include "libhcrypto.h"

#include <stdlib.h>
#include <stdio.h>

#include <openssl/evp.h>
#include <openssl/crypto.h>

#define BUFFER_SIZE 8192

size_t read_input(char*, size_t);

static const char *KEY = "YELLOW SUBMARINE";

int main(){
    char input[BUFFER_SIZE];

    size_t len = read_input(input, BUFFER_SIZE);
    if (len == BUFFER_SIZE){
        fprintf(stderr, "Error: Whole file was not read.\n");
        exit(27); // EFBIG - File too large
    }

    byte *outbytes = calloc(len, 1);
    int outlen = len;

    byte *bytes = calloc(len, 1);
    len = base64tobstring(input, len, bytes);

    // horrible hack!!
    len = (len/16)*16 + 16;
    /** EVP_CipherUpdate would only read in blocks of 
     * 16 bytes. Setting `len` to the closest
     * 16 multiple, padds the input with zeroes at the 
     * end (as we're using `calloc`).
     */


    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);
    EVP_CipherInit_ex(&ctx, EVP_aes_128_ecb(), NULL, NULL, NULL, 0);
    OPENSSL_assert(EVP_CIPHER_CTX_key_length(&ctx) == 16);
    //OPENSSL_assert(EVP_CIPHER_CTX_iv_length(&ctx) == 0);
    
    EVP_CipherInit_ex(&ctx, NULL, NULL, KEY, NULL, 0);

    while (1) 
    {
        // infinite loop.
        // TODO: read from file n bytes at a time.
        int ret = EVP_CipherUpdate(&ctx, outbytes, &outlen, bytes, len);
        if (outlen == 0) break;
        if(!ret){
            EVP_CIPHER_CTX_cleanup(&ctx);
            return 0;
        }
        for(size_t i = 0; i < outlen; i++)
            printf("%c", outbytes[i]);
    }
    printf("\n");
    return 0;
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
