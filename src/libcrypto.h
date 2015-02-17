#ifndef LIB_CRYPTO
#define LIB_CRYPTO

#include <stddef.h>

unsigned char char_to_byte(unsigned char);
unsigned char str_to_byte(const char*);
size_t str_to_bytes(const char*, unsigned char*, size_t);

char numtobase64(char);
char base64tonum(char);

char* byteatobase64a(unsigned char*, size_t, char*);
size_t base64tobstring(char*, size_t, unsigned char*);

unsigned char* xor_array(unsigned char*, unsigned char*, unsigned char*, size_t);

unsigned char break_singlechar_xor(const unsigned char*, size_t);
int decrypt_repeat_xor(unsigned char*, unsigned char*, size_t n);

int hamming(unsigned char*, unsigned char*, size_t);
int hamming_char(unsigned char, unsigned char);

#endif
