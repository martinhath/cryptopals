/**
 * author: MartinHaTh
 *
 * This file is a library of cryptography functions
 * and utilities, created primarily for the
 * Matasano crypto challenge.
 */

#include "libcrypto.h"

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
static int rate_string(unsigned char *str, size_t n)
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
    }
    return score;
}


/**
 * Breaks single character xor encoding of the
 * supplied string. Brute force, trying every
 * of the 256 chars.
 *
 * @param string Encoded string
 * @param n Length of the string
 * @return Most likely key
 */
unsigned char break_singlechar_xor(const unsigned char *string, size_t n)
{
    unsigned char key, chr, *xor_bytes;
    unsigned int i;
    int try_score, max_score;
    xor_bytes = malloc(n * sizeof(unsigned char));
    key = 0;
    max_score = 0;
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


/**
 * Decrypts a repeated XOR string with the supplied key.
 * The encrypted string will be destroyed, and replaced
 * with the resulting string.
 * Both strings are assumed to be null-terminated.
 *
 * @param string Encrypted key.
 * @param key Key
 * @param n Length of string
 * @return 0 on success, any other value on failure.
 */
int decrypt_repeat_xor(unsigned char *string, unsigned char *key, size_t n)
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

/**
 * Converts a single char to a byte.
 * @param c Char to be converted
 * @return Converted char
 */
unsigned char char_to_byte(unsigned char c)
{
    if ('A' <= c && c <= 'F')
        return c - 'A' + 10;
    if ('a' <= c && c <= 'f')
        return c - 'a' + 10;
    if ('0' <= c && c <= '9')
        return c - '0';
    return 0;
}

/**
 * Converts a single byte in string form to a char byte.
 * The function assumes that the string is well formed.
 *
 * Example: the string "20" would return 32.
 *
 * @param string The string containing one byte.
 * @return The byte.
 */
unsigned char str_to_byte(const char *string)
{
    return char_to_byte((unsigned const char) *string) * 0x10 +
           char_to_byte((unsigned const char) *(string + 1));
}

/**
 * Convert a string to an array of the bytes which are
 * making up the string.
 *
 * For instance, the string "a068" should insert the
 * array {160, 104} in target.
 *
 * @param string The string to read from
 * @param target The target array.
 * @param n The length of string. This is assumed to be large enough
 * (that is, n >= (size(string)+1)/2)
 * @return The number of bytes written (since you could
 * potentially write '\0', thus terminating the string).
 */
size_t str_to_bytes(const char *string, unsigned char *target, size_t n)
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

/**
 * 6 bit dec to base64 value
 *
 * @param n Decimal to be converted
 * @return Ascii value of base64 representation
 */
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

/**
 * Base64 char to 6 bit dec.
 *
 * @param c Base64 char to be converted
 * @return 6 bit number.
 */
char base64tonum(char c)
{
    if (c == '+') return 62;
    if (c == '/') return 63;
    if (c >= 'a') return c - 'a' + 26;
    if (c >= 'A') return c - 'A';
    if (c >= '0') return c - '0' + 52;
    fprintf(stderr, "%s %c (%d)\n", "Error! char not base64:", c, c);
    return -1;
}

/**
 * Byte array conversion to base64 byte array
 * The array size needs to be divisible by three.
 * In case the array length isn't divisible by three,
 * 0's should be appended.
 *
 * @param array The byte array
 * @param n Length of the array
 * @param b64 Array to store the base64 array. Is assumed to
 * be of size >= ceil(len/3)*4.
 * @return Pointer to the base64 array
 */
char *byteatobase64a(unsigned char *array, size_t n, char *b64)
{
    size_t i, j;
    int tmp;
    for (i = 0; i < n; i += 3) {
        tmp = (array[i] << 16) + (array[i + 1] << 8) + array[i + 2];
        for (j = 0; j < 4; j++)
            b64[j + (4 * i) / 3] = numtobase64((tmp >> (18 - j * 6)) & 63);
    }
    return b64;
}

/**
 * base64 string to byte string.
 *
 * @param b64string Base64 string to be converted
 * @param n Size of the Base64 string
 * @param array Target array to store the byte string in.
 * Size is assumed to be >= 3*strlen(b64)/4
 * @return Pointer to the target array
 */
unsigned char *base64tobstring(char *b64string, size_t n, unsigned char *array)
{
    size_t i, j, index;
    unsigned char num, tmp;
    for (i = 0; i < n; i += 4) {
        tmp = (unsigned char)(
              (base64tonum(b64string[i]) << 18) +
              (base64tonum(b64string[i + 1]) << 12) +
              (base64tonum(b64string[i + 2]) << 6) +
              (base64tonum(b64string[i + 3])));
        for (j = 0; j < 3; j++) {
            index = j + (3 * i) / 4;
            num = (tmp >> (16 - j * 8) & 0xff);
            array[index] = num;
        }
    }
    return array;
}

/**
 * XORs together two arrays, assumed to be length n
 *
 * @param a1 First array
 * @param a2 Second array
 * @param target Array to store the XOR in
 * @return n Pointer to target array
 */
unsigned char  *xor_array(unsigned char *a1, unsigned char *a2,
                          unsigned char *target, size_t n)
{
    size_t i;
    for (i = 0; i < n; i++)
        target[i] = a1[i] ^ a2[i];
    return target;
}

/**
 * Computes the hamming distance of the two strings
 * s1 and s2 of length n.
 *
 * @param s1 First string
 * @param s2 Second string
 * @param n Length of both strings
 * @return Hamming distance
 */
int hamming(unsigned char *s1, unsigned char *s2, size_t n)
{
    size_t i;
    int hamming;
    hamming = 0;
    for (i = 0; i < n; i++)
        hamming += hamming_char(s1[i], s2[i]);
    return hamming;
}

/**
 * Computes the hamming distance of the two chars
 *
 * @param c1 First char
 * @param c2 Second char
 * @return Hamming distance
 */
int hamming_char(unsigned char c1, unsigned char c2)
{
    static unsigned char BITS[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    int i, hamming;
    hamming = 0;
    c1 ^= c2;
    for (i = 0; i < 8; i++)
        hamming += ((c1 & BITS[i]) == BITS[i]);
    return hamming;
}

