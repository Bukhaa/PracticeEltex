#include <stdio.h> 
#include <stdlib.h>
 
int compare(const void * x1, const void * x2)   
{
  int num1 = atoi(*(const char **)x1);      
  int num2 = atoi(*(const char **)x2);
  return num1-num2;									
}
 
int main (int argc, char* argv[]){
  qsort(argv + 1, argc - 1, sizeof(char*), compare);      
  printf("Максимальный элемент: %s\n",argv[argc-1]);
  exit(EXIT_SUCCESS);
}