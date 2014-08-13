#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double log2(double n){
  return log(n)/log(2);
}

unsigned char stdintobin(){
  char bytes[3];
  unsigned char byte;
  int i;

  fgets(bytes, 3, stdin);

  for(i = 0; i < 2; i++){
    bytes[i] = tolower(bytes[i]);
    if(bytes[i] >= 'a'){
      bytes[i] -= 'a';
      bytes[i] += 10;
    }
    else{
      bytes[i] -= '0';
    }
  }
  byte = 16*bytes[0];
  byte += bytes[1];

  return byte;
}

char* numtobin(int num){
  char* string;
  int i;
  i = sizeof(char)*floor(log2(num)) + 1;
  string = (char*) malloc(i+1);
  string[i+1] = 0;
  while(i && num != 0){
    string[i--] = '0' + (!(num%2==0));
    num = num>>1;
  }
}

int main(){
  printf("%s\n", numtobin(10));;
  printf("%s\n", numtobin(4));;
  printf("%s\n", numtobin(22));;
}
