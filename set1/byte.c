#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 8192

unsigned char charantodec(char* chara, int n){
  char* input;
  unsigned char byte; 
  int i;

  input = (char*) malloc(sizeof(char)*n);
  strncpy(input, chara, 2);

  for(i = 0; i < n; i++){
    input[i] = tolower(input[i]);
    if(input[i] >= 'a'){
      input[i] -= 'a';
      input[i] += 10;
    }
    else{
      input[i] -= '0';
    }
  }
  byte = 16*input[0];
  byte += input[1];

  return byte;
}

unsigned char charatodec(char* chara){
  return charantodec(chara, strlen(chara));
}
int main(int argc, char* argv[]){
  char* input;
  int n, i;
  input = argv[1];
  n = strlen(input);
  n-=1;
  for(i = 0; i<n; i+=2){
    putchar(charantodec(input+i,2));
  }
  putchar('\n');
}
