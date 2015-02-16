#include "libcrypto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

size_t read_input(char *);
size_t find_keysize(unsigned char *);

int main()
{
    char input[BUFFER_SIZE] = {};
    unsigned char *bstring, *keys;
    unsigned char **splitstrings, **tstrings;
    size_t keysize, i, size, j, num_trans;
    i = read_input(input);
    size = 3 * i / 4;
    keysize = i - 1;
    bstring = calloc(size, sizeof(unsigned char));

    base64tobstring(input, i, bstring);
    printf("huehue\n");
    for (int a = 0; a < size; a++){
        printf("%02x", bstring[a]);
    }
    printf("\n");
    printf("huehue\n");
    /*i += 2;*/
    /*char* hurr = malloc(i * sizeof(char));*/
    /*byteatobase64a(bstring, i, hurr);*/
    /*for (int j = 0; j < i; j++){*/
    /*printf("%c", hurr[i]);*/
    /*}*/
    /*printf("\n");*/
    /*i -= 2;*/
    /* For each KEYSIZE, take the first KEYSIZE worth of bytes,
     * and the second KEYSIZE worth of bytes, and find the edit
     * distance between them. Normalize this result by dividing
     * by KEYSIZE. The KEYSIZE with the smallest normalized edit
     * distance is probably the key. You could proceed perhaps
     * with the smallest 2-3 KEYSIZE values. Or take 4 KEYSIZE
     * blocks instead of 2 and average the distances.*/
    /*keysize = find_keysize(bstring);*/
    keysize = 22;
    /* Resize the size of bstring so its a multiple
     * of the key size.*/
    j = (size / keysize + 1) * keysize - 1;
    bstring = realloc(bstring, j);
    for (i = size; i < j; i++)
        bstring[i] = 0;
    size = j;
    /* Now that you probably know the KEYSIZE: break the
     * ciphertext into blocks of KEYSIZE length.*/
    num_trans = size / keysize + 1;
    splitstrings = calloc(num_trans, sizeof(unsigned char *));
    for (i = 0; i < num_trans; i++){
        splitstrings[i] = bstring + i * keysize;
    }
    /* Now transpose the blocks: make a block that is the first
     * byte of every block, and a block that is the second byte
     * of every block, and so on.*/
    tstrings = calloc(keysize, sizeof(unsigned char *));
    for (i = 0; i < keysize; i++) {
        tstrings[i] = malloc(sizeof(unsigned char) * num_trans);
        for (j = 0; j < num_trans; j++)
            tstrings[i][j] = splitstrings[j][i];
    }
    /* Solve each block as if it was single-character XOR.
     * You already have code to do this.*/
    keys = malloc(keysize * sizeof(unsigned char) + 1);
    for (i = 0; i < keysize; i++){
        *keys++ = break_singlechar_xor(tstrings[i], num_trans);
    }
    keys -= keysize;
    keys[keysize] = '\0';
    /* For each block, the single-byte XOR key that produces
     * the best looking histogram is the repeating-key XOR key
     * byte for that block. Put them together and you have the key.*/
    decrypt_repeat_xor(bstring, keys, size);
    for (i = 0; i < size; i++)
        printf("%c", bstring[i]);
    printf("\n");
    return 0;
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
    float keysize_norm, keysize_norm2, keysize_norm_min;
    keysize_norm_min = 99;
    keysize_cand = 2;
    for (keysize = 2; keysize <= 40; keysize++) {
        keysize_norm = hamming(bstring, bstring +
                keysize, keysize) / (float)  keysize;
        /*keysize_norm = hamming(bstring, bstring + keysize, keysize);*/
        /*keysize_norm2 = hamming(bstring + 2*keysize,*/
        /*bstring + 3*keysize, keysize);*/
        /*keysize_norm = (keysize_norm + keysize_norm2)/(keysize*2.0);*/

        printf("Keysize: %zu\tKeysize_norm: %3f\n", keysize, keysize_norm);
        if (keysize_norm < keysize_norm_min) {
            keysize_norm_min = keysize_norm;
            keysize_cand = keysize;
        }
    }
    printf("Keysize: %zu\n", keysize_cand);
    return keysize_cand;
}

