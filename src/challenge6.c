#include "libcrypto.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void solve(const byte*, size_t, size_t);
size_t read_input(char *);
size_t find_keysize(unsigned char *);

int main()
{
    char input[BUFFER_SIZE];

    size_t i = read_input(input);
    size_t size = 3 * i / 4;

    byte *bstring = calloc(size, sizeof(unsigned char));
    size = base64tobstring(input, i, bstring);

    size_t keysize = find_keysize(bstring);
    keysize = 0;

    while(keysize++< 40){
        printf("\n\n=== KEYSIZE: %zu ===\n", keysize);
        solve(bstring, size, keysize);
    }
}


void solve(const byte* string, size_t len, size_t keysize){
    /* Now that you probably know the KEYSIZE: break the
    * ciphertext into blocks of KEYSIZE length.*/
    byte *str = malloc(len * 1);
    memmove(str, string, len);

    size_t num_blocks = len/keysize + 1;
    byte **blocks = malloc(num_blocks * sizeof(byte*));

    for (size_t i = 0; i < num_blocks; i++){
        blocks[i] = str + (i * keysize);
        for (size_t j = 0; j < keysize; j++){
        }
    }

    /*Now transpose the blocks: make a block that is the first*/
    /*byte of every block, and a block that is the second byte*/
    /*of every block, and so on.*/

    byte **transposed_blocks = malloc(keysize * sizeof(byte*));
    for (size_t i = 0; i < keysize; i++){
        transposed_blocks[i] = malloc(num_blocks * 1);
        for (size_t j = 0; j < num_blocks; j++){
            transposed_blocks[i][j] = blocks[j][i];
        }
    }

    /*Solve each block as if it was single-character XOR.*/
    /*You already have code to do this.*/
    /*For each block, the single-byte XOR key that produces*/
    /*the best looking histogram is the repeating-key XOR key*/
    /*byte for that block. Put them together and you have the key.*/
    byte *key = malloc(keysize * 1 + 1);
    for (size_t i = 0; i < keysize; i++){
        key[i] = break_singlechar_xor(
                transposed_blocks[i], num_blocks);

    }
    key[keysize] = '\0';


    decrypt_repeat_xor(str, key, len);
    // `str` is now decrypted.
    for (size_t i = 0; i < len; i++){
        printf("%c", str[i]);
    }
    printf("\n");
}

size_t read_input(char *input)
{
    char c;
    size_t i = 0;
    while ((c = (char) getchar()) != EOF)
        input[i++] = c;
    i--;
    input[i] = 0;
    return i;
}

size_t find_keysize(unsigned char *bstring)
{
    size_t keysize, keysize_cand;
    float keysize_norm, keysize_norm_min;
    keysize_norm_min = INT_MAX;
    keysize_cand = 2;

    for (keysize = 2; keysize <= 40; keysize++) {
        keysize_norm = hamming(bstring, bstring +
                keysize, keysize) / (float)  keysize;
        /*printf("Keysize: %zu\tKeysize_norm: %3f\n", keysize, keysize_norm);*/
        if (keysize_norm < keysize_norm_min) {
            keysize_norm_min = keysize_norm;
            keysize_cand = keysize;
        }
    }
    /*printf("Keysize: %zu\n", keysize_cand);*/
    return keysize_cand;
}

