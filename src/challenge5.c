#include "libcrypto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(){
    char* cipher = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
    size_t cipher_size = strlen(cipher);
    size_t nbytes = (cipher_size + 1) / 2;

    unsigned char* bytestr = malloc(nbytes * sizeof(unsigned char));
    str_to_bytes(cipher, bytestr, cipher_size);

    decrypt_repeat_xor(bytestr, "ICE", nbytes);

    printf("%s\n", bytestr);
}
