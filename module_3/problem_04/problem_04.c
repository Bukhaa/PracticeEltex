#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>

#define read_ 0
#define write_ 1

int main(int argc, char* argv[]){
	int fd[2];
	pid_t pid;
	size_t i;
	int num;
	
	if (argc != 2) {
        printf("Введите количество аргументов!\n");
        exit(EXIT_FAILURE);
    }
	
	int count_number = atoi(argv[1]);
	
	 if(pipe(fd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
	
	pid = fork();
	if(pid == -1){
		perror("fork");
		close(fd[read_]);
		close(fd[write_]);
		exit(EXIT_FAILURE);
	} else if(0 == pid){
		
		close(fd[read_]);
		
		srand(time(NULL));
		
		for(i = 0; i < count_number; ++i){
			
			int number = rand() % 100;
			int res = write(fd[write_], &number, sizeof(int));
			if(res < 0){
				
				perror("write");
				close(fd[write_]);
				exit(EXIT_FAILURE);
			}
		}
		
		close(fd[write_]);
		exit(EXIT_SUCCESS);
		
	} else {
		
		close(fd[write_]);
		
		char * filename = "out_04.txt";
		
		FILE *fp = fopen(filename, "w");
		
		if (!fp) {
			printf("Eror of open file");
			exit(EXIT_FAILURE);
			close(fd[read_]);
		}
	
		for(i = 0; i < count_number; ++i){
			
			int res = read(fd[read_], &num, sizeof(int));
			if(res < 0){
				
				perror("read");
				close(fd[read_]);
				exit(EXIT_FAILURE);
			} 
			printf("Число %ld: %d\n", i, num);
			fprintf(fp,"%d\n", num);
		}
		
		close(fd[read_]);
		fclose(fp);
	}
	exit(EXIT_SUCCESS);
}
