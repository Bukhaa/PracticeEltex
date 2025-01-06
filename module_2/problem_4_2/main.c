#include <stdio.h>

#define SIZE 8

typedef struct{
	
	int elem;
	int priority;
	
}node;

typedef struct {
	
	node elems[SIZE];
	int size;
	
}priority_queue;

size_t queue_size(priority_queue *pq){
	return pq->size;
}

void init_priority_queue(priority_queue *pq) {pq->size = -1;}
int is_empty_priority_queue(priority_queue *pq) {return pq->size == -1;}
int is_full_priority_queue(priority_queue *pq) {return pq->size == SIZE-1;}


void add_element(priority_queue *pq, int data, int priority) {
    if (!is_full_priority_queue(pq)) {
        pq->size++;
        int i;
        for (i = pq->size; i > 0 && (pq->elems[i - 1].priority > priority ); i--) {
            pq->elems[i] = pq->elems[i - 1];
        }
        pq->elems[i].elem = data;
        pq->elems[i].priority = priority;
    }
	else{
		printf("Очередь заполнена!\n");
		return;
	}
}

void pop_first_element(priority_queue *pq){
	
	if(!is_empty_priority_queue(pq))
	{
		for(size_t i = 0; i < pq->size; ++i)
		{
			pq->elems[i].elem = pq->elems[i+1].elem;
			pq->elems[i].priority = pq->elems[i+1].priority;
		}
		pq->size -= 1;
	}
	else{
		printf("Очередь пустая!\n");
	}
	
}

int pop_with_priority(priority_queue *pq, int priority){
	
	if (!is_empty_priority_queue(pq)) {
		
		int delete_elem;
		
        for(size_t i = 0; i <= pq-> size; ++i){
			if(pq->elems[i].priority == priority){
				delete_elem = pq->elems[i].elem;
				for(size_t j = i; j < pq->size; ++j){
					pq->elems[j].elem = pq->elems[j+1].elem;
					pq->elems[j].priority = pq->elems[j+1].priority;
				}
				
				pq->size -= 1;
				return delete_elem;
			}
			
		}
		printf("Такого приоритета нету!\n");
		return 0;
    }
	else{
		printf("Очередь пустая!\n");
		return 0;
	}
	
}

int pop_with_priority_upgrade(priority_queue *pq, int priority){
	
	if (!is_empty_priority_queue(pq)) {
		
		int delete_elem;
	
	while(printf >= 0){
        for(size_t i = 0; i <= pq-> size; ++i){
			if(pq->elems[i].priority == priority){
				delete_elem = pq->elems[i].elem;
				for(size_t j = i; j < pq->size; ++j){
					pq->elems[j].elem = pq->elems[j+1].elem;
					pq->elems[j].priority = pq->elems[j+1].priority;
				}
				
				pq->size -= 1;
				return delete_elem;
			}
			
		}
		priority -= 1;
	}
		
    }
	else{
		printf("Очередь пустая!\n");
		return 0;
	}
	
}

void display(priority_queue *pq) {
    for (int i = 0; i <= pq->size; ++i) {
        printf("(%d, %d)\n", pq->elems[i].elem, pq->elems[i].priority);
    }
}


int main(){
	priority_queue pq;
    init_priority_queue(&pq);

    add_element(&pq, 5, 1);
    add_element(&pq, 1000, 3);
    //add_element(&pq, 15, 4);
    add_element(&pq, 10, 3);
    add_element(&pq, 20, 5);
    add_element(&pq, 20, 3);
    add_element(&pq, 500, 2);
	add_element(&pq, 444, 0);
	
	printf("Display: \n");
	display(&pq);
	
	printf("pop_first_element\n");
	pop_first_element(&pq);
	printf("Display: \n");
	display(&pq);
	printf("add element\n");
	add_element(&pq, 444, 0);
	printf("Display: \n");
	display(&pq);
	printf("Deleted element: %d\n", pop_with_priority_upgrade(&pq, 3));
	printf("Display: \n");
	display(&pq);
	
	
	return 0;
}