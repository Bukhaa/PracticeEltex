#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	
	size_t i;
	int sum = 0;
	
	for(i = 0; i < argc; ++i){
		sum += atoi(argv[i]);
	}
	
	printf("Сумма аргументов: %d \n", sum);
	
	exit(EXIT_SUCCESS);
}
