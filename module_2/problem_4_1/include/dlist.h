#include<stdio.h>

typedef struct node{
	struct node* next;
	struct node* prev;
	PhoneBook* data;
}node;

int search(node* head, const char* lastName);
node* insert_sort(node *head, PhoneBook* pb);
node* delete_contact(node *head, const char* lastName);
void update(node* head, const char* lastName, PhoneBook* new_contact);
void print_dlist(node* head);
node* delete_front(node* head);
void clear(node* head);
