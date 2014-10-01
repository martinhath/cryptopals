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
 * Converts a single char to a byte.
 * @param Char to be converted
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
    return -1;
}

/**
 * Converts a single byte in string form to a char byte.
 * The function assumes that the string is well formed.
 *
 * Example: the string "20" would return 32.
 *
 * @param The string containing one byte.
 * @return The byte.
 */
unsigned char str_to_byte(const char *string)
{
    return char_to_byte(*string) * 16 + char_to_byte(*(string + 1));
}

/**
 * Convert a string to an array of the bytes which are
 * making up the string.
 *
 * For instance, the string "a068" should return the
 * array {160, 104}.
 *
 * @param The string to read from
 * @param The target array. This is assumed to be large enough
 * (that is, size >= (size(string)+1)/2)
 * @return The number of bytes written (since you could
 * potentially write '\0', thus terminating the string).
 */
size_t str_to_bytes(const char *string, unsigned char *target, size_t n)
{
    int i;
    char *str = NULL;

    if (n % 2 != 0)
    {
        str = malloc(sizeof(char) * (n + 1));
        str[0] = '0';
        strncpy(str + 1, string, n);
    }
    i = 0;
    while (string[i] && string[i + 1])
    {
        target[i / 2] = str_to_byte(string + i);
        i += 2;
    }
    return i / 2;
}

/**
 * 6 bit dec to ascii value
 * @param Decimal to be converted
 * @return Ascii value of base64 representation
 */
char numtobase64(size_t n)
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
 * Byte array conversion to base64 byte array
 * The array size needs to be divisible by three.
 * In case the array length isn't divisible by three,
 * 0's should be appended.
 *
 * @param The byte array
 * @param Length of the array
 * @param Array to store the base64 array. Is assumed to
 * be of size >= ceil(len/3)*4.
 * @return Pointer to the base64 array
 */
unsigned char* byteatobase64a(unsigned char* array, size_t n, char* b64)
{
    int tmp, i, j;
    for (i = 0; i < n; i += 3)
    {
        tmp = (array[i] << 16) + (array[i + 1] << 8) + array[i + 2];
        for (j = 0; j < 4; j++)
        {
            b64[j + (4 * i) / 3] = numtobase64((tmp >> (18 - j * 6)) & 63);
        }
    }
    return b64;
}


