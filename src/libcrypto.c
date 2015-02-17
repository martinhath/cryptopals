/**
 * author: MartinHaTh
 *
 * This file is a library of cryptography functions
 * and utilities, created primarily for the
 * Matasano crypto challenge.
 */

#include "libcrypto.h"

#include <limits.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * Helper function for break_singlechar_xor.
 * Rates a string. Higher rating means more likely
 * to contain real words and sentences.
 *
 * @param str String to be rated
 * @param n Length of string
 * @return Rating
 */
static int rate_string(byte *str, size_t n)
{
    unsigned int i;
    int score;
    score = 0;
    for (i = 0; i < n; i++) {
        switch (str[i]) {
        case ' ':
            score += 7;
            break;
        case 'a':
        case 'e':
        case 's':
            score += 5;
            break;
        case 'i':
        case 'c':
        case 'h':
            score += 2;
            break;
        }
        if (!isalnum(str[i]))
            score -= 4;
    }
    return score;
}


byte break_singlechar_xor(const byte *string, size_t n)
{
    byte key, chr, *xor_bytes;
    unsigned int i;
    int try_score, max_score;
    xor_bytes = malloc(n * sizeof(byte));
    key = 0;
    max_score = INT_MIN;
    for (chr = 0; chr != 255; chr++) {
        for (i = 0; i < n; i++)
            xor_bytes[i] = string[i] ^ chr;
        if ((try_score = rate_string(xor_bytes, n)) > max_score) {
            key = chr;
            max_score = try_score;
        }
    }
    free(xor_bytes);
    return key;
}


int decrypt_repeat_xor(byte *string, byte *key, size_t n)
{
    unsigned int i;
    size_t ksize;
    ksize = strlen((char *) key);
    i = 0;
    while (n -- > 0) {
        *string ^= key[i++];
        string++;
        if (i >= ksize)
            i = 0;
    }
    return 0;
}

byte char_to_byte(byte c)
{
    if ('A' <= c && c <= 'F')
        return c - 'A' + 10;
    if ('a' <= c && c <= 'f')
        return c - 'a' + 10;
    if ('0' <= c && c <= '9')
        return c - '0';
    return 0;
}

byte str_to_byte(const char *string)
{
    return char_to_byte((unsigned const char) *string) * 0x10 +
           char_to_byte((unsigned const char) *(string + 1));
}

size_t str_to_bytes(const char *string, byte *target, size_t n)
{
    size_t i;
    char *str = NULL;
    if (n % 2 != 0) {
        str = malloc(sizeof(char) * (n + 1));
        str[0] = '0';
        strncpy(str + 1, string, n);
    }
    i = 0;
    while (string[i] && string[i + 1]) {
        target[i / 2] = str_to_byte(string + i);
        i += 2;
    }
    free(str);
    return i / 2;
}

char numtobase64(char n)
{
    if (n <= 25)
        return 'A' + n;
    if (n <= 51)
        return 'a' + n - 26;
    if (n <= 61)
        return '0' + n - 52;
    return n == 62 ? '+' : '/';
}

char base64tonum(char c)
{
    if (c == '+') return 62;
    if (c == '/') return 63;
    if (c >= 'a') return c - 'a' + 26;
    if (c >= 'A') return c - 'A';
    if (c >= '0') return c - '0' + 52;
    if (c == '\n' || c == '\r' || c == '\0') return -1;
    fprintf(stderr, "%s %c (%d)\n", "Error! char not base64:", c, c);
    return -1;
}

char *byteatobase64a(byte *array, size_t n, char *b64)
{
    size_t i, j;
    int tmp;
    for (i = 0; i < n; i += 3) {
        tmp = (array[i] << 16) + (array[i + 1] << 8) + array[i + 2];
        for (j = 0; j < 4; j++)
            b64[j + (4 * i) / 3] = numtobase64((tmp >> (18 - j * 6)) & 63);
    }
    j = i - n;
    while (j-- > 0)
        b64[(j) + (4 * n + 2) / 3] = '=';

    return b64;
}

size_t base64tobstring(const char *b64string, size_t n, byte *array)
{
    size_t i, j, index;
    int tmp;
    byte num;
    for (i = 0; i < n-3; i += 4) {
        tmp = (base64tonum(b64string[i]) << 18) +
              (base64tonum(b64string[i + 1]) << 12) +
              (base64tonum(b64string[i + 2]) << 6) +
              (base64tonum(b64string[i + 3]));
        for (j = 0; j < 3; j++) {
            index = j + (3 * i) / 4;
            num = (tmp >> (16 - j * 8) & 0xff);
            array[index] = num;
        }
    }
    size_t numeq = 0;
    while (b64string[--n] == '=')
        numeq++;
    size_t len = (3 * i) / 4 - numeq;
    array[len] = '\0';
    return len;
}

byte  *xor_array(byte *a1, byte *a2,
                          byte *target, size_t n)
{
    size_t i;
    for (i = 0; i < n; i++)
        target[i] = a1[i] ^ a2[i];
    return target;
}

int hamming(byte *s1, byte *s2, size_t n)
{
    size_t i;
    int hamming;
    hamming = 0;
    for (i = 0; i < n; i++)
        hamming += hamming_char(s1[i], s2[i]);
    return hamming;
}

int hamming_char(byte c1, byte c2)
{
    static byte BITS[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    int i, hamming;
    hamming = 0;
    c1 ^= c2;
    for (i = 0; i < 8; i++)
        hamming += ((c1 & BITS[i]) == BITS[i]);
    return hamming;
}

