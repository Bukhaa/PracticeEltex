#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include "contact_list.h"
#include "dlist.h"

extern int ind,current_count;

int search(node* head, const char* lastName){
	if(head == NULL){
		//printf("Список пустой!\n");
		return -1;
	}
	
	node* tmp = head;
	while(tmp != NULL){
		if(strcmp(tmp->data->person.lastName, lastName) == 0){
			//printf("Элемент найдден: ");
			return 1;
		}
		tmp = tmp->next;
		
	}
	//printf("Такого элемента нет!\n");
    return -1;	
}

node* insert_sort(node *head, PhoneBook* pb){
	
	int chek_person = search(head, pb->person.lastName);
	
	if(chek_person == -1){
	
		node* new_node = malloc(sizeof(node));
		new_node->data = pb;
		
		if(head == NULL){
			new_node->prev = NULL;
			new_node->next = NULL;
			return new_node;
		}
		
		if(strcmp(pb->person.lastName, head->data->person.lastName) < 0) { 
			new_node->next = head; 
			new_node->prev = NULL; 
			head->prev = new_node;
			return new_node; 
		} 
		
		node* tmp = head;
		while(tmp->next != NULL){ 
		
			if(strcmp(pb->person.lastName, tmp->next->data->person.lastName) < 0 ) { 
				new_node->next = tmp->next; 
				new_node->prev = tmp; 
				tmp->next->prev = new_node; 
				tmp->next = new_node; 
				
				return head; 
			} 
			tmp = tmp->next; 
		} 
		
			tmp->next = new_node;
			new_node->prev = tmp;
			new_node->next = NULL;
		
		return head;
	}
	
} 

node* delete_contact(node *head, const char* lastName){
	if(head == NULL)
		return head;
	
	int chek_person = search(head, lastName);
	
    if(chek_person == 1){
	
		
		
		node* curr = head;
			
		while(strcmp(curr->data->person.lastName, lastName) != 0)
			curr = curr->next;
		
		if(curr->prev != NULL) 
			curr->prev->next = curr->next;
		 
		else 
			head = curr->next; // Если удаляемый узел — первый
		
		if(curr->next != NULL)
			curr->next->prev = curr->prev;
		
		else
			curr->prev->next == NULL;
    
		free(curr);
	}
	return head;
}

void update(node* head, const char* lastName, PhoneBook* new_contact) {
    if (head == NULL) {
        return ; // Узел не найден
    }

    int chek_person = search(head, lastName);
	
    if(chek_person == 1){
		
		node* curr = head;
			
		while(strcmp(curr->data->person.lastName, lastName) != 0)
			curr = curr->next;
		
		curr->data = new_contact;
	}
}


void print_dlist(node* head){
	
	if(head == NULL)
		return;
	
	node* tmp = head;
	
	while(tmp != NULL){ 
        printf("Имя: %s, Фамилияяяяя: %s, Отчество: %s\n", 
               tmp->data->person.firstName, 
               tmp->data->person.lastName, 
               tmp->data->person.famName);
        printf("Адрес работы: %s, Должность: %s\n", 
               tmp->data->person_job_info.JobAddress, 
               tmp->data->person_job_info.Position);
        printf("Телефон: %s, Email: %s\n", 
               tmp->data->person_relax_info.PhoneNumber, 
               tmp->data->person_relax_info.EmailAdress);
        printf("Соц. сеть: %s, Мессендж: %s\n\n", 
               tmp->data->person_relax_info.ReferenceSocialNetwork, 
               tmp->data->person_relax_info.ReferenceMessage);
		tmp = tmp->next;
		
	}
}

node* delete_front(node* head){
	
	node* curr = head->next;
	if(curr !=NULL){
		curr->prev =NULL;
	}
	free(head);
	
	return curr;
}

void clear(node* head){
	
	while(head != NULL)
		head = delete_front(head);
}
