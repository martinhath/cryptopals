#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HEXSTRING "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
#define SCORE_LIM 30

unsigned char* decipher(unsigned char* in, int len, unsigned char* cipher, int clen){
  unsigned char *ret;
  int i;
  ret = (unsigned char*) malloc(sizeof(unsigned char)*len);
  for(i = 0; i < len; i++){
    ret[i] = in[i] ^ cipher[i%clen];
  }
  return ret;
}

int score(unsigned char* in, int len){
  int s, i;
  s = 0;
  for(i = 0; i < len; i++){
    switch(in[i]){
      case ' ': s+=5; 
                break;
      case 'a': s+=3; 
                break;
      case 'e': s+=4; 
                break;
      case 'i': s+=2; 
                break;
      case 'o': s+=2; 
                break;
      case 's': s+=1; 
                break;
    }
  }
  return s;
}

int htoc(char *input, unsigned char *output){
  char *in2;
  int n, i; 
  n = strlen(input);
  if(n%2==1){
    in2 = (char*) calloc(n, sizeof(char));
    in2[0] = '0';
    input = strcat(in2, input);
  }
  for(i = 0; i < (n+1)/2; i++){
    sscanf(input, "%2x", output++);
    input+=2;
  }
  return (n+1)/2;
}

int main(){
  unsigned char byte, *string, *tmpstr;
  int len, sc;
  len = strlen(HEXSTRING);
  string = (unsigned char*) malloc(sizeof(unsigned char)*(len+1)/2);
  len = htoc(HEXSTRING, string);

  for(byte = 1; byte > 0; byte++){
    tmpstr = decipher(string, len, &byte, 1);
    if((sc=score(tmpstr, len)) > SCORE_LIM)
      printf("Score: %d\tByte: %d\n%s\n\n", sc, byte, tmpstr);
    free(tmpstr);
  }
  return 0;
}
