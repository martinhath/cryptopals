#include "libcrypto.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tuple.h"

#define BUFFER_SIZE 4096

void solve(const byte*, size_t, size_t);
size_t read_input(char *);
size_t find_keysize(byte *);

int main()
{
    char input[BUFFER_SIZE];

    size_t i = read_input(input);
    size_t size = 3 * i / 4;

    byte *bstring = calloc(size, sizeof(byte));
    size = base64tobstring(input, i, bstring);

    size_t keysize = find_keysize(bstring);
    keysize = 0;

    while(keysize++< 40){
        /*printf("\n\n=== KEYSIZE: %zu ===\n", keysize);*/
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
    free(blocks);

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
    for (size_t i = 0; i < keysize; i++){
        free(transposed_blocks[i]);
    }
    free(transposed_blocks);

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


size_t find_keysize(byte *bytes)
{
#define MAX_KEY  40
#define MIN_KEY  2
#define SIZE  MAX_KEY - MIN_KEY + 1

    size_t keysize, keysize_cand;
    float keysize_norm, keysize_norm_min;
    Tuple pairs[SIZE];

    keysize_norm_min = INT_MAX;
    keysize_cand = MIN_KEY;

    for (keysize =  MIN_KEY; keysize <= MAX_KEY; keysize++) {
        keysize_norm = hamming(bytes, bytes + keysize, keysize);
        float k2 = hamming(bytes+2*keysize, bytes + 3*keysize, keysize);
        keysize_norm = (k2 + keysize_norm) / (2*keysize);

        Tuple t = {.weight = keysize_norm, .value = keysize};
        pairs[keysize-MIN_KEY] = t;
    }

    tuplesort(pairs, SIZE);

    for (int i = 0; i < 7; i++)
        printf("%2zu (%3.2f)\n", pairs[i].value, pairs[i].weight);

    printf("Keysize: %zu\n", keysize_cand);
    return keysize_cand;
}

