#ifndef LIB_CRYPTO
#define LIB_CRYPTO

#include <stddef.h>

typedef unsigned char byte;

/**
 * Converts a single char to a byte.
 * @param c Char to be converted
 * @return Converted char
 */
byte char_to_byte(byte c);
/**
 * Converts a single byte in string form to a char byte.
 * The function assumes that the string is well formed.
 *
 * Example: the string "20" would return 32.
 *
 * @param string The string containing one byte.
 * @return The byte.
 */
byte str_to_byte(const char *string);
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
size_t str_to_bytes(const char *string, byte *target, size_t n);

/**
 * 6 bit dec to base64 value
 *
 * @param n Decimal to be converted
 * @return Ascii value of base64 representation
 */
char numtobase64(char n);
/**
 * Base64 char to 6 bit dec.
 *
 * @param c Base64 char to be converted
 * @return 6 bit number.
 */
char base64tonum(char c);

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
char* byteatobase64a(byte *array, size_t n, char* b64);
/**
 * base64 string to byte string.
 *
 * @param b64string Base64 string to be converted
 * @param n Size of the Base64 string
 * @param array Target array to store the byte string in.
 * Size is assumed to be >= 3*strlen(b64)/4
 * @return Returns length of decoded string
 */
size_t base64tobstring(const char *b64string, size_t n, byte *array);

/**
 * XORs together two arrays, assumed to be length n
 *
 * @param a1 First array
 * @param a2 Second array
 * @param target Array to store the XOR in
 * @return n Pointer to target array
 */
byte* xor_array(byte *a1, byte *a2, byte *target, size_t n);

/**
 * Breaks single character xor encoding of the
 * supplied string. Brute force, trying every
 * of the 256 chars.
 *
 * @param string Encoded string
 * @param n Length of the string
 * @return Most likely key
 */
byte break_singlechar_xor(const byte *string, size_t n);
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
int decrypt_repeat_xor(byte *string, byte *key, size_t n);

/**
 * Computes the hamming distance of the two strings
 * s1 and s2 of length n.
 *
 * @param s1 First string
 * @param s2 Second string
 * @param n Length of both strings
 * @return Hamming distance
 */
int hamming(byte *s1, byte *s2, size_t n);
/**
 * Computes the hamming distance of the two chars
 *
 * @param c1 First char
 * @param c2 Second char
 * @return Hamming distance
 */
int hamming_char(byte c1, byte c2);

#endif
