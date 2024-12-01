#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>

#define MAX_NUMBERS 10
#define SHM_SIZE sizeof(int) * (MAX_NUMBERS + 2)
#define SEM_NAME "semaphore"
#define SHM_NAME "shm_memory"

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

int main() {
	
    int shmid, num, shm_fd;
    int *shm_ptr;
    sem_t* sem;
    srand(time(NULL));

    if((shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0660)) == -1){
	perror("shm_open failed!\n");
	exit(EXIT_FAILURE);
    }
	
    ftruncate(shm_fd, SHM_SIZE);
	
    if((shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)) == (int*) -1){
	perror("mmap failed!\n");
	exit(EXIT_FAILURE);
    }
	
    if ((sem = sem_open(SEM_NAME, O_CREAT, 0660, 1)) == SEM_FAILED){
	perror("error sem_open\n");
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
			
	    if(sem_wait(sem) == -1){
		perror("error sem_wait\n");
		exit(EXIT_FAILURE);
	    }
            
            int count = shm_ptr[0]; 
            int min = INT_MAX;
	    int max = INT_MIN;
            
            find_min_max(shm_ptr, count, &min, &max);
            shm_ptr[count + 1] = min;
            shm_ptr[count + 2] = max;
			
            if(sem_post(sem) == -1){
		perror("error sem_post\n");
		exit(EXIT_FAILURE);
	    }
			
	    sleep(1);
        } 
		
        exit(EXIT_SUCCESS);
    } else { 
	
	int sets_count = 0;
	
        while (chek) {
			
	    if(sem_wait(sem) == -1){
		perror("error sem_wait\n");
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
			
	    if(sem_post(sem) == -1){
		perror("error sem_post\n");
		exit(EXIT_FAILURE);
	    }
            
	    sleep(1);
			
	    if(sem_wait(sem) == -1){
		perror("error sem_wait\n");
		exit(EXIT_FAILURE);
	    }
			
            printf("Минимум: %d, Максимум: %d\n", shm_ptr[count + 1], shm_ptr[count + 2]);

            sets_count++; 
			
	    if(sem_post(sem) == -1){
                perror("error sem_post\n");
	        exit(EXIT_FAILURE);
	    }
	    sleep(1); 
        }
		
       printf("Количество обработанных наборов: %d\n", sets_count);
    }
	
    if(munmap(shm_ptr, SHM_SIZE) == -1){
	perror("munmap failed!\n");
	exit(EXIT_FAILURE);
    }
	
    if(shm_unlink(SHM_NAME) == -1){
    	perror("shm_unlink failed!\n");
	exit(EXIT_FAILURE);
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
