#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

#define FILENAME "out_04.txt"
#define read_ 0
#define write_ 1

volatile sig_atomic_t file_access = 1; 


void handle_sigusr1(int signum) {
    file_access = 0; 
}

void handle_sigusr2(int signum) {
    file_access = 1; 
}

int main(int argc, char* argv[]) {
    int fd[2];
    pid_t pid;
    size_t i;
    int num;
    int count_number;

    if (argc != 2) {
        printf("Введите количество аргументов!\n");
        exit(EXIT_FAILURE);
    }

    count_number = atoi(argv[1]);

    if (pipe(fd) == -1) {
        perror("Ошибка создания канала");
        exit(EXIT_FAILURE);
    }

    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);

    pid = fork();
    if (pid == -1) {
        perror("Ошибка fork");
	close(fd[read_]);
	close(fd[write_]);
        exit(EXIT_FAILURE);
    } else if (0 == pid) { 
        close(fd[write_]);
    
	FILE *fp = fopen(FILENAME, "r");
        if (fp == NULL) {
            printf("Ошибка открытия файла");
	    close(fd[read_]);
            exit(EXIT_FAILURE);
        }
    
        for (i = 0; i < count_number; ++i) {
            
	    while (!file_access)
	        pause();
			
	int res = read(fd[read_], &num, sizeof(int));
	if(res < 0){
	    perror("read");
	    close(fd[read_]);
	    exit(EXIT_FAILURE);
	}
          
	    fscanf(fp,"%d\n", &num);
	    printf("%d\n",num);
        }
	close(fd[read_]);
	fclose(fp);
        exit(EXIT_SUCCESS);

    } else { 
        close(fd[read_]);
	srand(time(NULL));
    
        FILE *fp = fopen(FILENAME, "w");
        if (fp == NULL) {
            printf("Ошибка открытия файла");
	    close(fd[write_]);
            exit(EXIT_FAILURE);
        }

        for (i = 0; i < count_number; ++i) {
			
            kill(pid, SIGUSR1); 
            int number = rand() % 100;	
            int res = write(fd[write_], &number, sizeof(int));
	    if(res < 0){
	        perror("write");
		close(fd[write_]);
		exit(EXIT_FAILURE);
	    }
			
	    fprintf(fp, "%d\n", number);
            kill(pid, SIGUSR2); 
            sleep(1); 
        }
	close(fd[write_]);
        fclose(fp);
        wait(NULL);
    }
	exit(EXIT_SUCCESS);
}


