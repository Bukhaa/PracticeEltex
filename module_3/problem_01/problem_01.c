#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void square(int length) {
	printf("Площадь квадрата со стороной %d: %d\n", length, length * length);
}
	
int main(int argc, char* argv[]) {
	
	size_t i;
	pid_t pid;
	
	if (argc < 3) {
		
        	printf("Eror in arguments\n");
        	exit(EXIT_FAILURE);
    	}
	
	int count_op = argc / 2;
	pid = fork();
	
	if (-1 == pid) {
        	perror("fork"); 
            	exit(EXIT_FAILURE); 
   	 } else if (0 == pid) {
		
		for (i = 1; i <=count_op; ++i){
			square(atoi(argv[i]));
		}
		exit(EXIT_SUCCESS);
    	}
	
	else {
		
		for (i = count_op + 1; i < argc; ++i) 
			square(atoi(argv[i]));
		
		wait(NULL);
	}
	
	exit(EXIT_SUCCESS);
}
