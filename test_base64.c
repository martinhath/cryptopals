#include "src/libcrypto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static size_t _count = 0;

void assertEq(char* s1, char* s2){
    if (strcmp(s1, s2) != 0){
        printf("Assertion failed (test #%zu). \n\t%s\nshould be\n\t%s\n\n", _count,  s1, s2);
    }
}

void testBase64(char* string, char* base){
    _count++;

    size_t len = strlen(string);
    size_t size = (size_t) ((len+2)/3.0)*4;
    char* b64array = calloc(size+1, 1);
    byteatobase64a(string, len, b64array);
    b64array[size] = '\0';
    assertEq(b64array, base);
}

int main()
{
    testBase64("any carnal pleasure.", "YW55IGNhcm5hbCBwbGVhc3VyZS4=");
    testBase64("any carnal pleasure" , "YW55IGNhcm5hbCBwbGVhc3VyZQ==");
    testBase64("any carnal pleasur"  , "YW55IGNhcm5hbCBwbGVhc3Vy");
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
/*char *byteatobase64a(unsigned char *array, size_t n, char *b64)*/
