#include "../src/libcrypto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int assertEq(char*, char*);
void test_to_base64(char*, char*);
void test_from_base64(char*, char*);
void run_test_base64();


static size_t _count = 0;
static size_t _passes = 0;

/**
 * All assertions should return 0 on success.
 */
int assertEq(char* s1, char* s2){
    if (strcmp(s1, s2) != 0){
        printf("Assertion failed (test #%zu).\
                \n\t%s\nshould be\n\t%s\n\n",
                _count, s1, s2);
        return -1;
    }
    return 0;
}

void test_to_base64(char* string, char* base){
    _count++;

    size_t len = strlen(string);
    size_t size = (size_t) ((len+2)/3.0)*4;
    char* b64array = calloc(size+1, 1);
    byteatobase64a(string, len, b64array);
    b64array[size] = '\0';
    if (assertEq(b64array, base) == 0)
        _passes++;
}

void test_from_base64(char* base64, char* string){
    _count++;

    size_t len = strlen(base64);
    size_t size = (3*len)/4;

    char* str = calloc(size, 1);
    base64tobstring(base64, len, str);

    if (assertEq(str, string) == 0)
        _passes++;
}

void run_test_base64()
{
    test_to_base64("any carnal pleasure.",
                   "YW55IGNhcm5hbCBwbGVhc3VyZS4=");
    test_to_base64("any carnal pleasure",
                   "YW55IGNhcm5hbCBwbGVhc3VyZQ==");
    test_to_base64("any carnal pleasur",
                   "YW55IGNhcm5hbCBwbGVhc3Vy");

    test_from_base64("YW55IGNhcm5hbCBwbGVhc3VyZS4=",
                     "any carnal pleasure.");
    test_from_base64("YW55IGNhcm5hbCBwbGVhc3VyZQ==",
                     "any carnal pleasure");
    test_from_base64("YW55IGNhcm5hbCBwbGVhc3Vy",
                     "any carnal pleasur");

    printf("=== Test Summary ===\n");
    printf("%5d tests\n", _count);
    printf("%5d passes\n", _passes);
    if (_passes != _count)
        printf("--- Number of fails: %d\n",
                _count-_passes);
    else
        printf("=== All tests passed. ===\n");
}
