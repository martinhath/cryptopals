#ifndef LIB_CRYPTO
#define LIB_CRYPTO

#include <stddef.h>

unsigned char char_to_byte(unsigned char);
unsigned char str_to_char(const char*);
size_t str_to_bytes(const char*, unsigned char*, size_t);

char numtobase64(size_t);

char* byteatobase64a(unsigned char*, size_t, char*);
unsigned char* base64tobstring(char*, size_t, unsigned char*);

unsigned char* xor_array(unsigned char*, unsigned char*, unsigned char*, size_t);

int hamming(unsigned char*, unsigned char*, size_t);
int hamming_char(unsigned char, unsigned char);

#endif
