#include "libcrypto.h"

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int read_input(char *);
int find_keysize(unsigned char *);

int main()
{
    char input[BUFFER_SIZE];
    unsigned char *bstring;
    unsigned char **splitstrings, **tstrings;
    int keysize, i, size, j, num_trans;
    i = read_input(input);
    size = 3 * i / 4;
    keysize = i - 1;
    bstring = calloc(sizeof(unsigned char) * size, 0);
    base64tobstring(input, i, bstring);
    /* For each KEYSIZE, take the first KEYSIZE worth of bytes,
     * and the second KEYSIZE worth of bytes, and find the edit
     * distance between them. Normalize this result by dividing
     * by KEYSIZE. The KEYSIZE with the smallest normalized edit
     * distance is probably the key. You could proceed perhaps
     * with the smallest 2-3 KEYSIZE values. Or take 4 KEYSIZE
     * blocks instead of 2 and average the distances.*/
    keysize = (1+find_keysize(bstring)) / 2;
    printf("bstring\n");
    for (i = 0; i < size; i++) {
        if (i % 20 == 0 && i != 0) printf("\n");
        printf("%.2x ", bstring[i]);
    }
    printf("\nEND bstring END\n");
    /* Now that you probably know the KEYSIZE: break the
     * ciphertext into blocks of KEYSIZE length.*/
    num_trans = size / keysize + 1;
    printf("size: %d\tkeysize:%d\tnum_trans:%d\n", size, keysize, num_trans);
    printf("%d", bstring);
    printf("%s\n", bstring);
    splitstrings = calloc(sizeof(unsigned char *) * num_trans, 0);
    printf("%d", splitstrings);
    printf("%s\n", bstring);
    for (i = 0; i < num_trans; i++) {
        splitstrings[i] = bstring + i * keysize;
        for (j = 0; j < keysize; j++)
            printf("%.2x ", splitstrings[i][j]);
        printf("\n");
    }
    /* Now transpose the blocks: make a block that is the first
     * byte of every block, and a block that is the second byte
     * of every block, and so on.*/
    tstrings = calloc(sizeof(unsigned char **) * keysize, 0);
    for (i = 0; i < keysize; i++) {
        tstrings[i] = malloc(sizeof(unsigned char *) * num_trans);
        for (j = 0; j < num_trans; j++) {
            tstrings[i][j] = splitstrings[j][i];
            printf("%.2x ", tstrings[i][j]);
        }
        printf("\n");
    }
    /* Solve each block as if it was single-character XOR.
     * You already have code to do this.*/
    /* For each block, the single-byte XOR key that produces
     * the best looking histogram is the repeating-key XOR key
     * byte for that block. Put them together and you have the key.*/
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
        if (keysize_norm > keysize_norm_max) {
            keysize_norm_max = keysize_norm;
            keysize_cand = keysize;
        }
    }
    printf("%s%d\n", "Probable keysize: ", keysize_cand);
    return keysize_cand;
}

