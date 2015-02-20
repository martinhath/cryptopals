#include "libhcrypto.h"

#include <stdlib.h>
#include <stdio.h>

#include <openssl/evp.h>
#include <openssl/crypto.h>

#define BUFFER_SIZE 1024

size_t read_input(char *, size_t);

static const char *KEY = "YELLOW SUBMARINE";

size_t read_input(char *input, size_t size)
{
    int c;
    size_t i = 0;
    while (i < size &&
            (c = getchar()) != EOF)
        input[i++] = (char) c;
    return i;
}

int main()
{
    /**
     * Strategy:
     * we want to read a chuck from a file, and
     * convert it from base64. The new byte chunk
     * will be of length (3*SIZE)/4.
     * With SIZE = 1024, the length of the
     * converted string is 768.
     *
     * Then, for each string, we decrypt it
     * using openssl, and print it to stdout.
     *
     * As we're using ECB, we need the string length
     * to be a multiple of the key length, which it
     * is with SIZE = 1024 (16*48 = 768).
     */
    char input[BUFFER_SIZE];
    byte encrypted[(BUFFER_SIZE * 3) / 4];
    byte decrypted[(BUFFER_SIZE * 3) / 4];
    int decrypt_len;
    
    EVP_CIPHER_CTX ctx;
    EVP_CIPHER_CTX_init(&ctx);
    
    EVP_CipherInit_ex(&ctx, EVP_aes_128_ecb(), NULL, NULL, NULL, 0);
    OPENSSL_assert(EVP_CIPHER_CTX_key_length(&ctx) == 16);
    
    EVP_CipherInit_ex(&ctx, NULL, NULL, (const unsigned char*) KEY, NULL, 0);
    
    while (1) {
        size_t input_len = read_input(input, BUFFER_SIZE);
        if (input_len == 0) break;
        size_t encrypt_len = base64tobstring(input, input_len, encrypted);
        
        int ret = EVP_CipherUpdate(&ctx, decrypted, &decrypt_len,
                                   encrypted, (int) encrypt_len);
        if (!ret) {
            EVP_CIPHER_CTX_cleanup(&ctx);
            return 0;
        }
        for (int i = 0; i < decrypt_len; i++)
            printf("%c", decrypted[i]);
    }
    if (!EVP_CipherFinal_ex(&ctx, decrypted, &decrypt_len)) {
        EVP_CIPHER_CTX_cleanup(&ctx);
        return 0;
    }
    for (int i = 0; i < decrypt_len; i++)
        printf("%c", decrypted[i]);
    return 0;
}

