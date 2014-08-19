#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char* axor(char* first, char* second){
  char* xor = (char*) malloc(sizeof(char)*strlen(first)); 
  int i = 0;
  while(i<strlen(first)){
    xor[i] = first[i]^second[i];
    i++;
  }
  return xor;
}

int main(){
  char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];

  fgets(buf1, BUFFER_SIZE, stdin);
  fgets(buf2, BUFFER_SIZE, stdin);

  printf("%x\n", axor(buf1, buf2));
}
