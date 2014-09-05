#include "libcrypto.h"

#include <stdio.h>

int main(){
        char *str = "8020a9f2";
        int i;
        unsigned char tar[4] = {32};

        if (str_to_bytes(str, tar, 4) != 4){
                printf("%s\n", "Error!!");
        }
        for (i = 0; i<4; i++){
                printf("%d ", tar[i]);
        }
        printf("%s", "\n");

        return 0;
}
