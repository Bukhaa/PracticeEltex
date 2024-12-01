#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define MAX_NUMBERS 10
#define SHM_SIZE sizeof(int) * (MAX_NUMBERS + 2)

int *shm_ptr;
volatile sig_atomic_t chek = 1; 

void handle_sigint(int sig) {
    chek = 0;
}

void find_min_max(int *data, int count, int *min, int *max) {
	
    if(count == 1) {*min = data[1]; *max = data[1];}
    for (int i = 1; i < count + 1; i++) {
        if (data[i] < *min) {
            *min = data[i];
        }
        if (data[i] > *max) {
            *max = data[i];
        }
    }
}

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main() {
	
    int shmid, num, semid;
    key_t key;
	
    srand(time(NULL));

    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0660)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    
    if ((shm_ptr = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
	
	if ((key = ftok(".", 's')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

	
    semid = semget(key, 1, IPC_CREAT | 0660);
    if(semid == -1){
	perror("Ошибка семафора\n");
	exit(EXIT_FAILURE);
    }
    
    struct sembuf lock_res = {0,-1,0};
    struct sembuf rel_res[2] = {{0,0,0},
				{0,1,0}};
    union semun arg;
    arg.val = 1;

    if(semctl(semid, 0, SETVAL, arg) == -1){
	perror("Ошибка инициализации семафора\n");
	exit(EXIT_FAILURE);
    }

    signal(SIGINT, handle_sigint);
	
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        while (chek) {
			
	    if((semop(semid, &lock_res, 1)) == -1){
	        perror("Lock failed!\n");
                exit(EXIT_FAILURE);
            }
            
            int count = shm_ptr[0]; 
            int min = INT_MAX;
	    int max = INT_MIN;
            
            find_min_max(shm_ptr, count, &min, &max);
            shm_ptr[count + 1] = min;
            shm_ptr[count + 2] = max;
			
	    if((semop(semid, rel_res, 2)) == -1){
                perror("Unlock failed!\n");
                exit(EXIT_FAILURE);
            }
			
	    sleep(1);
        } 
		
        exit(EXIT_SUCCESS);
    } else { 
	
	int sets_count = 0;
	
        while (chek) {
			
	   if((semop(semid, &lock_res, 1)) == -1){
		perror("Lock failed!\n");
            	exit(EXIT_FAILURE);
            }
			
	    int count = rand() % MAX_NUMBERS + 1;
            shm_ptr[0] = count; 
			
	    printf("Записываем %d случайных чисел: ", count);
	    for (int i = 0; i < count; i++) {
		shm_ptr[i + 1] = rand() % 100; 
		printf("%d ", shm_ptr[i + 1]);
	    }
	    printf("\n");
			
	   if((semop(semid, rel_res, 2)) == -1){
                perror("Unlock failed!\n");
                exit(EXIT_FAILURE);
            }
            
	   sleep(1);
			
	    if((semop(semid, &lock_res, 1)) == -1){
		perror("Lock failed!\n");
            	exit(EXIT_FAILURE);
            }
			
            printf("Минимум: %d, Максимум: %d\n", shm_ptr[count + 1], shm_ptr[count + 2]);

            sets_count++; 
			
	    if((semop(semid, rel_res, 2)) == -1){
                perror("Unlock failed!\n");
                exit(EXIT_FAILURE);
            }
	    sleep(1); 
        }
		
	   printf("Количество обработанных наборов: %d\n", sets_count);
    }
	if(semctl(semid, 0, IPC_RMID) < 0){
		perror("Ошибка удаления семафора!\n");
		exit(EXIT_FAILURE);
    	}
	if(shmdt(shm_ptr) == -1){
		perror("shmdt failed!\n");
		exit(EXIT_FAILURE);
	}
        if(shmctl(shmid, IPC_RMID, NULL) == -1){
		perror("shmctl failed!\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
