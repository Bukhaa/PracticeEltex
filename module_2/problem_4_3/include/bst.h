#include<stdio.h>

typedef struct bst_node{
	
	PhoneBook* data;
	struct bst_node* right;
	struct bst_node* left;
	
}bst_node;

bst_node* insert(bst_node* root, PhoneBook* newcontact);
 bst_node* delete_contact(bst_node* root, const char* lastName);
 bst_node* update_contact(bst_node* root, const char* lastName, PhoneBook* new_contact);
 void clear(bst_node* root);
 void destruct(bst_node* root);
 void print_bst(bst_node* root);
 