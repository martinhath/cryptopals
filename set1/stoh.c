#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* stoc(char* string){
  int n; 
  char* ret;
  n = strlen(string);
  ret = (char*) malloc(sizeof(char)*n);
  while(string){
  }
  return ret;
}

char* stoh(char* string){
  char *ret; 
  int i, n;

  n = strlen(string);
  ret = (char*) malloc(sizeof(char)*(n+1)/2);

  for(i = 0; i < n; i+=2){
    if(i==0 && n%2==1){
      i--;
      sscanf(string, "%x", ret);
      continue;
    }
    sscanf(string, "%2x", ret);
  }
  return ret;
}
