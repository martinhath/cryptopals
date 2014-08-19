#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
  char *first, *second;
  int i, n;
  first = argv[1];
  second = argv[2];
  n = 0;
  while(*first++ ||  *second++){
    n++;
  }
  first = argv[1];
  second = argv[2];
  for(i = 0; i < n; i++){
    printf("%02x", first[i]^second[i]);
    printf("\n\t%x  %x\n", first[i], second[i]);
  }
  printf("\n");
  
}
