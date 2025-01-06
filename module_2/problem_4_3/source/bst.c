#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include "contact_list.h"
#include "bst.h"

extern int ind,current_count;

bst_node* insert(bst_node* root, PhoneBook* newcontact) {

    if (root == NULL) {
        bst_node* temp = (bst_node*)malloc(sizeof(bst_node));
        temp->data = newcontact;
        temp->right = temp->left = NULL;
        current_count++;
        return temp;
    }

    // Сравнение по фамилии
    int cmp = strcmp(newcontact->person.lastName, root->data->person.lastName);
    if (cmp < 0) {
        root->left = insert(root->left, newcontact);
    } else if (cmp > 0) {
        root->right = insert(root->right, newcontact);
    } else {
        printf("Контакт с фамилией %s уже существует.\n", newcontact->person.lastName);
    }

    return root;

}

 bst_node* delete_contact(bst_node* root, const char* lastName) {
    if (root == NULL) {
        return root; // Узел не найден
    }

    int cmp = strcmp(lastName, root->data->person.lastName);
    if (cmp < 0) {
        root->left = delete_contact(root->left, lastName);
    } else if (cmp > 0) {
        root->right = delete_contact(root->right, lastName);
    } else {
        // Узел найден
        if (root->left == NULL) {
            bst_node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            bst_node* temp = root->left;
            free(root);
            return temp;
        }

        // Узел с двумя детьми: находим минимальный узел в правом поддереве
        bst_node* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }

        // Заменяем данные узла и удаляем его
        root->data = temp->data;
        root->right = delete_contact(root->right, temp->data->person.lastName);
    }
    return root;
}

 bst_node* update_contact(bst_node* root, const char* lastName, PhoneBook* new_contact) {
    if (root == NULL) {
        return root; // Узел не найден
    }

    int cmp = strcmp(lastName, root->data->person.lastName);
    if (cmp < 0) {
        root->left = update_contact(root->left, lastName, new_contact);
    } else if (cmp > 0) {
        root->right = update_contact(root->right, lastName, new_contact);
    } else {
        // Узел найден
       
	   root->data = new_contact;
        
    }
    return root;
}




void clear(bst_node* root){
	if (root == NULL)
		return;

	clear(root->left);
	clear(root->right);
	free(root);
}

void destruct(bst_node* root){
	clear(root);
	root = NULL;
}

void print_bst(bst_node* root) {
    if (root != NULL) {
        print_bst(root->left); 
        printf("Имя: %s, Фамилия: %s, Отчество: %s\n", 
               root->data->person.firstName, 
               root->data->person.lastName, 
               root->data->person.famName);
        printf("Адрес работы: %s, Должность: %s\n", 
               root->data->person_job_info.JobAddress, 
               root->data->person_job_info.Position);
        printf("Телефон: %s, Email: %s\n", 
               root->data->person_relax_info.PhoneNumber, 
               root->data->person_relax_info.EmailAdress);
        printf("Соц. сеть: %s, Сообщение: %s\n\n", 
               root->data->person_relax_info.ReferenceSocialNetwork, 
               root->data->person_relax_info.ReferenceMessage);
        print_bst(root->right); 
    }
}