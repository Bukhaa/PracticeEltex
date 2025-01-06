#include <stdio.h>
#include <stdlib.h>
#include "contact_list.h"


int main(){
	PhoneBook pb[MAX_PHONE_BOOK_LEN] = {0};
	int op;
	
	printf("What do you do?\n");
	printf("If you want add contact, please press 1\n");
	printf("If you want delete contact, please press 2\n");
	printf("If you want update contact, please press 3\n");
	printf("If you want display all contact, please press 4\n");
	printf("If you want exit, please press 0\n");
	
	while(1)
	{
		printf("Please, select a function\n");
		scanf("%d", &op);
		PhoneBook NewContact = {0};
		
		switch (op)
		{
			case 1:
			printf("Add contact: \n");
			    SetData(&NewContact);
				addPerson(pb,&NewContact);
				break;
			case 2:
				printf("Delete contact: \n");
				PhoneBook ContactDel = {0};
				printf("Input contact: \n");
				
				char fn[MAX_NAME_LEN];
				char ln[MAX_NAME_LEN];
				char fam[MAX_NAME_LEN];
				
				printf("Enter first name: ");
				scanf("%19s",fn);
				printf("\nEnter last name: ");
				scanf("%19s",ln);
				printf("\nEnter ochestvo: ");
				scanf("%19s",fam);
				
				PersonInit(&(ContactDel.person), fn, ln, fam);
				deletePerson(pb,&ContactDel);
				break;
			case 3:
				printf("Update contact: \n");
				PhoneBook PrevContact = {0};
			    printf("Input contact: \n");
				
				char fn_u[MAX_NAME_LEN];
				char ln_u[MAX_NAME_LEN];
				char fam_u[MAX_NAME_LEN];
				
				printf("Enter first name: ");
				scanf("%19s",fn_u);
				printf("\nEnter last name: ");
				scanf("%19s",ln_u);
				printf("\nEnter ochestvo: ");
				scanf("%19s",fam_u);
				
				PersonInit(&(PrevContact.person), fn_u, ln_u, fam_u);
				
				printf("Input new contact: \n");
				PhoneBook UpdateContact = {0};
				
				SetData(&UpdateContact);
				updatePersonInfo(pb,&PrevContact,&UpdateContact);
				break;
			case 4:
				printf("Display contact: \n");
				displayPhoneBook(pb);
				break;
			case 0:
				exit(0);
			default :
				printf("This function undefined!\n");

		}
		
	}
	
	return 0;
}