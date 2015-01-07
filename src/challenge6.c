#include "libcrypto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

int read_input(char *);
int find_keysize(unsigned char *);

int main()
{
    char input[BUFFER_SIZE];
    unsigned char *bstring, *keys;
    unsigned char **splitstrings, **tstrings;
    int keysize, i, size, j, num_trans;
    i = read_input(input);
    size = 3 * i / 4;
    keysize = i - 1;
    bstring = calloc(size, sizeof(unsigned char));
    base64tobstring(input, i, bstring);
    /* For each KEYSIZE, take the first KEYSIZE worth of bytes,
     * and the second KEYSIZE worth of bytes, and find the edit
     * distance between them. Normalize this result by dividing
     * by KEYSIZE. The KEYSIZE with the smallest normalized edit
     * distance is probably the key. You could proceed perhaps
     * with the smallest 2-3 KEYSIZE values. Or take 4 KEYSIZE
     * blocks instead of 2 and average the distances.*/
    keysize = find_keysize(bstring);
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
    for (i = 0; i < num_trans; i++)
        splitstrings[i] = bstring + i * keysize;
    /* Now transpose the blocks: make a block that is the first
     * byte of every block, and a block that is the second byte
     * of every block, and so on.*/
    tstrings = calloc(sizeof(unsigned char *) * keysize, 0);
    for (i = 0; i < keysize; i++) {
        tstrings[i] = malloc(sizeof(unsigned char) * num_trans);
        for (j = 0; j < num_trans; j++)
            tstrings[i][j] = splitstrings[j][i];
    }
    /* Solve each block as if it was single-character XOR.
     * You already have code to do this.*/
    keys = malloc(keysize * sizeof(unsigned char) + 1);
    for (i = 0; i < keysize; i++)
        *keys++ = break_singlechar_xor(tstrings[i], strlen((char *)tstrings[i]));
    keys -= keysize;
    keys[keysize] = 0;
    /* For each block, the single-byte XOR key that produces
     * the best looking histogram is the repeating-key XOR key
     * byte for that block. Put them together and you have the key.*/
    decrypt_repeat_xor(bstring, keys, size);
    for (i = 0; i < size; i++)
        printf("%c", bstring[i]);
    return 0;
}

int read_input(char *input)
{
    char c;
    int i = 0;
    while ((c = getchar()) != EOF)
        input[i++] = c;
    i--;
    input[i] = 0;
    return i;
}

int find_keysize(unsigned char *bstring)
{
    int keysize, keysize_cand;
    float keysize_norm, keysize_norm_max;
    keysize_norm_max = 0;
    keysize_cand = 2;
    for (keysize = 2; keysize <= 40; keysize++) {
        keysize_norm = ((float) hamming(bstring, bstring + keysize, keysize)) / keysize;
        printf("Keysize: %d\tKeysize_norm: %3f\n", keysize, keysize_norm);
        if (keysize_norm > keysize_norm_max) {
            keysize_norm_max = keysize_norm;
            keysize_cand = keysize;
        }
    }
    printf("Keysize: %d\n", keysize_cand);
    return keysize_cand;
}

