#ifndef LIB_CRYPTO
#define LIB_CRYPTO

#include <stddef.h>

unsigned char char_to_byte(unsigned char);
unsigned char str_to_char(const char*);
size_t str_to_bytes(const char*, unsigned char*, size_t);

#endif
