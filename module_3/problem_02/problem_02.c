#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	
	while(1){
		size_t i = 0;
		int count_args;
		pid_t status;
		char path[20];
		
		printf("Это командный интепретатор\n");
		printf("Введите имя запускаемой программы: \n");
		scanf("%s", path);
		
		if(strcmp(path,"exit") == 0)
			break;
		
		printf("Введите количество аргументов: \n");
		scanf("%d", &count_args);
		
		char* mass[count_args + 1];
		for(; i < count_args; ++i){
			char s[6];
			scanf(" %s", s);
			mass[i] = malloc(strlen(s) + 1);
			strcpy(mass[i], s); 
		}
		
		mass[i] = NULL;
		
		pid_t pid = fork();
		
		if (-1 == pid) {
				perror("fork"); 
				exit(EXIT_FAILURE); 
		} else if (0 == pid) {
			if(execvp(path, mass) == -1){
				perror("Ошибка execv");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		
		else{
			wait(NULL);
			for(size_t i = 0; i < count_args; ++i){
				free(mass[i]); 
			}
		}
	}
	
	exit(EXIT_SUCCESS);
}
