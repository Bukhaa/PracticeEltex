#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/sem.h>

#define FILENAME "out_04.txt"
#define read_ 0
#define write_ 1
#define COUNTPROC 2

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main(int argc, char* argv[]) {
    int fd[2];
    pid_t pid;
    size_t i;
    int num, semid;
    int count_number; 
    key_t key;

    if (argc != 2) {
        printf("Введите количество аргументов!\n");
        exit(EXIT_FAILURE);
    }

    count_number = atoi(argv[1]);

    if (pipe(fd) == -1) {
        perror("Ошибка создания канала");
        exit(EXIT_FAILURE);
    }

    if ((key = ftok(".", 'a')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

	
    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if(semid == -1){
	perror("Ошибка семафора\n");
	exit(EXIT_FAILURE);
    }
    
    struct sembuf read_lock_res = {0,-1,0};
    struct sembuf read_rel_res = {0,1,0};			    

    struct sembuf write_lock_res = {0,-COUNTPROC,0};
    struct sembuf write_rel_res = {0,COUNTPROC,0};

    union semun arg;
    arg.val = COUNTPROC;

    if(semctl(semid, 0, SETVAL, arg) == -1){
	perror("Ошибка инициализации семафора\n");
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
            printf("Ошибка открытия файла");
            close(fd[read_]);
            exit(EXIT_FAILURE);
         }
    
        for (i = 0; i < count_number; ++i) {

	    if((semop(semid, &read_lock_res, 1)) == -1){
		perror("Lock failed!\n");
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
            
	    if((semop(semid, &read_rel_res, 1)) == -1){
                perror("Unlock failed!\n");
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
            printf("Ошибка открытия файла");
            close(fd[write_]);
            exit(EXIT_FAILURE);
        }


        for (i = 0; i < count_number; ++i) {
			
            if((semop(semid, &write_lock_res, 1)) == -1){
		perror("Lock failed!\n");
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
	    
            if((semop(semid, &write_rel_res, 1)) == -1){
		perror("Unlock failed!\n");
		exit(EXIT_FAILURE);
	    }

           sleep(1); 
        }
	
	fclose(fp);
	close(fd[write_]);
        wait(NULL);
    }
    
    if(semctl(semid, 0, IPC_RMID) < 0){
	perror("Ошибка удаления семафора!\n");
	exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
