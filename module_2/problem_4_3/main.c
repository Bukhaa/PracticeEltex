#include<stdio.h>
#include "contact_list.h"
#include "bst.h"


void test_1(){
	bst_node* root = NULL; 
	
    PhoneBook newContact1;
    SetData(&newContact1); 
    root = insert(root, &newContact1); 
		
    PhoneBook newContact2;
	SetData(&newContact2); 
    root = insert(root, &newContact2);	
	
	PhoneBook newContact3;
	SetData(&newContact3); 
    root = insert(root, &newContact3);	
	
	PhoneBook newContact4;
	SetData(&newContact4); 
    root = insert(root, &newContact4);
    
    print_bst(root);
	
	destruct(root);
}

void test_2(){
	bst_node* root = NULL; 
	
    PhoneBook newContact1;
    SetData(&newContact1); 
    root = insert(root, &newContact1); 
		
    PhoneBook newContact2;
	SetData(&newContact2); 
    root = insert(root, &newContact2);	
	
	PhoneBook newContact3;
	SetData(&newContact3); 
    root = insert(root, &newContact3);	
	
	PhoneBook newContact4;
	SetData(&newContact4); 
    root = insert(root, &newContact4);
    
    print_bst(root);
	
	printf("Delete contact with lastname %s: \n", newContact1.person.lastName);
	root = delete_contact(root, newContact1.person.lastName);
	print_bst(root);
	
	destruct(root);
	
}

void test_3(){
	bst_node* root = NULL; 
	
    PhoneBook newContact1;
    SetData(&newContact1); 
    root = insert(root, &newContact1); 
		
    PhoneBook newContact2;
	SetData(&newContact2); 
    root = insert(root, &newContact2);	
	
	PhoneBook newContact3;
	SetData(&newContact3); 
    root = insert(root, &newContact3);	
	
	PhoneBook newContact4;
	SetData(&newContact4); 
    root = insert(root, &newContact4);
    
    print_bst(root);
	
	printf("data for update: \n");
	PhoneBook newContact5;
	SetData(&newContact5); 
	
	printf("Update contact with lastname %s: \n", newContact3.person.lastName);
	root = update_contact(root, "no_update", &newContact5);
	
	print_bst(root);
	
	printf("Delete contact with lastname %s: \n", newContact1.person.lastName);
	root = delete_contact(root, newContact1.person.lastName);
	print_bst(root);
	
	destruct(root);
}



int main(){
	
	printf("Test #1: \n");
	test_1();
	printf("Test #2: \n");
	test_2();
	printf("Test #3: \n");
	test_3();
	
	return 0;
}