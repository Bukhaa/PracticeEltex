#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>

#define FILENAME "out_10.txt"
#define read_ 0
#define write_ 1
#define SEM_NAME "semaphore"

int main(int argc, char* argv[]) {
    int fd[2];
    pid_t pid;
    size_t i;
    int num;
    int count_number; 
    sem_t* sem;

    if (argc != 2) {
        printf("Введите количество аргументов!\n");
        exit(EXIT_FAILURE);
    }

    count_number = atoi(argv[1]);

    if (pipe(fd) == -1) {
        perror("Ошибка создания канала");
        exit(EXIT_FAILURE);
    }

    if ((sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0660, 1)) == SEM_FAILED){
	perror("error se_open\n");
	exit(EXIT_FAILURE);
    }

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
            perror("Ошибка открытия файла");
            close(fd[read_]);
            exit(EXIT_FAILURE);
         }
    
        for (i = 0; i < count_number; ++i) {
	    
            if(sem_wait(sem) == -1){
		perror("error sem_wait\n");
		exit(EXIT_FAILURE);
	    }
	    
	    int res = read(fd[read_], &num, sizeof(int));
	    if(res < 0){
		perror("read");
		close(fd[read_]);
	        exit(EXIT_FAILURE);
	    }
          
	    fscanf(fp,"%d\n", &num);
	    printf("%d\n",num);
	    
	    if(sem_post(sem) == -1){
		perror("error sem_post\n");
		exit(EXIT_FAILURE);
	    }

            sleep(1);
        }
	fclose(fp);
	close(fd[read_]);
        exit(EXIT_SUCCESS);

    } else { 
        close(fd[read_]);
	srand(time(NULL));

	FILE *fp = fopen(FILENAME, "w");
        if (fp == NULL) {
            perror("Ошибка открытия файла");
            close(fd[write_]);
            exit(EXIT_FAILURE);
        }


        for (i = 0; i < count_number; ++i) {
	    
 	    if(sem_wait(sem) == -1){
                perror("error sem_wait\n");
                exit(EXIT_FAILURE);
            }
	    
            int number = rand() % 100;
			
            int res = write(fd[write_], &number, sizeof(int));
	    if(res < 0){
		perror("write");
		close(fd[write_]);
		exit(EXIT_FAILURE);
	    }
	    	    
	    fprintf(fp, "%d\n", number);
	    
	    if(sem_post(sem) == -1){
                perror("error sem_post\n");
                exit(EXIT_FAILURE);
            }

           sleep(1); 
        }
	
	fclose(fp);
	close(fd[write_]);
        wait(NULL);
    }
    
    if(sem_close(sem) == -1){
	perror("error sem_close\n");
	exit(EXIT_FAILURE);
    }

    if(sem_unlink(SEM_NAME) == -1){
	perror("error sem_unlink\n");
	exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
