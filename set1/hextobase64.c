#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 4096

double log2(double n){
  return log(n)/log(2);
}

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

char* chartobin(unsigned char num){
  char* string;
  int i;
  string = (char*) malloc(9);
  string[8] = 0;
  for(i = 0; i < 8; i++){
    string[i] = '0';
  }
  i = 7;
  while(num != 0){
    string[i--] = '0' + (!(num%2==0));
    num = num>>1;
  }
  return string;
}

char tobase64(int n){
  if(n<26){
    return n + 'A';
  }
  else if(n<52){
    return n + 'a' - 26;
  }
  else if(n<62){
    return n + '0' - 52;
  }
  return n==62?'+':'/';
}

int binntoint(char* bin, int n){
  int i, ret;
  ret = 0;
  for(i = 0; i < n; i++){
    ret += bin[n-i-1] == '1' ? pow(2, i) :0;
  }
  return ret;
}

int main_test(){
  printf("%s\n", "charatodec:");
  printf("00 = %d\n", charatodec("00"));
  printf("0f = %d\n", charatodec("0f"));
  printf("ff = %d\n", charatodec("ff"));
  printf("20 = %d\n", charatodec("20"));
  putchar('\n');

  printf("%s\n", "chartobin");
  printf("%s%s\n", "100	= ", chartobin(100));
  printf("%s%s\n", "32	= ", chartobin(32));
  printf("%s%s\n", "255	= ", chartobin(255));
  printf("%s%s\n", "0	  = ", chartobin(0));

  printf("%s\n", "binntoint");
  printf("%s%d\n", "00001100 = ", binntoint("00001100", 8));
  printf("%s%d\n", "10101010 = ", binntoint("10101010", 8));
  printf("%s%d\n", "11111111 = ", binntoint("11111111", 8));
  printf("%s%d\n", "00000000 = ", binntoint("00000000", 8));

  return 0;
}

int main(){
  char binarystring[BUFFER_SIZE], inputstring[BUFFER_SIZE/8];
  int i, n;

  /**
  main_test();
  return 0;
  */
  
  fgets(inputstring, BUFFER_SIZE/8, stdin);

  n = strlen(inputstring);
  n-=1;

  for(i = 0; i<n; i+=2){
    strncat(binarystring, chartobin(charantodec(inputstring+i,2)), 8);
  }

  n = (strlen(binarystring))/6;
  for(i = 0; i<n; i++){
    putchar(tobase64(binntoint(binarystring+i*6, 6)));
  }
  putchar('\n');

  return 0;
}

