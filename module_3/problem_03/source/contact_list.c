#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include "contact_list.h"

#define MAX_NAME_LEN 20 
#define JOB_ADDRESS_LEN 30
#define POSITION_LEN 30
#define PHONE_NUMBER_LEN 15
#define EMAIL_ADDRESS_LEN 20
#define REFERENCE_SOCIAL_NETWORK_LEN 30
#define REFERENCE_MESSAGE_LEN 30
#define MAX_PHONE_BOOK_LEN 100

int ind = -1;

size_t current_count = 0;

void PersonInit(Person *p, char* fn, char* ln, char* fam){
	
	strncpy(p->firstName, fn, MAX_NAME_LEN);
	strncpy(p->lastName, ln, MAX_NAME_LEN);
	strncpy(p->famName, fam, MAX_NAME_LEN);
}

void PersonJobInfoInit(PersonJobInfo *p, char* adr, char* pos){
	
	if (adr[0] == '-') {
        strcpy(p->JobAddress, ""); 
    } else {
        strcpy(p->JobAddress, adr);
    }

    if (pos[0] == '-') {
        strcpy(p->Position, ""); 
    } else {
        strcpy(p->Position, pos);
    }
}

void PersonRelaxInit(PersonRelaxInfo *p, char* phone, char* email, char* ref_soc, char* ref_msg){
	if (phone[0] == '-') {
        strcpy(p->PhoneNumber, ""); 
    } else {
        strcpy(p->PhoneNumber, phone);
    }

    if (email[0] == '-') {
        strcpy(p->EmailAdress, ""); 
    } else {
        strcpy(p->EmailAdress, email);
    }
	
	if (ref_soc[0] == '-') {
        strcpy(p->ReferenceSocialNetwork, ""); 
    } else {
        strcpy(p->ReferenceSocialNetwork, ref_soc);
    }
	
	if (ref_msg[0] == '-') {
        strcpy(p->ReferenceMessage, ""); 
    } else {
        strcpy(p->ReferenceMessage, ref_msg);
    }
	
}

void findPerson(PhoneBook *pb, PhoneBook *newcontact){
	int i;
	ind = -1;
	for(size_t i = 0; i < current_count; ++i){
		if((strcmp(pb[i].person.firstName, newcontact->person.firstName) == 0) && (strcmp(pb[i].person.lastName, newcontact->person.lastName) == 0) && (strcmp(pb[i].person.famName, newcontact->person.famName) == 0))
		{
			ind = i;break;
		}
			
	}
		
}

void SwapInfo(PhoneBook *pb, PhoneBook *newcontact){
	strcpy(pb->person.firstName,newcontact->person.firstName);
	strcpy(pb->person.lastName,newcontact->person.lastName);
	strcpy(pb->person.famName,newcontact->person.famName);
	strcpy(pb->person_job_info.JobAddress,newcontact->person_job_info.JobAddress);
	strcpy(pb->person_job_info.Position,newcontact->person_job_info.Position);
	strcpy(pb->person_relax_info.PhoneNumber,newcontact->person_relax_info.PhoneNumber);
	strcpy(pb->person_relax_info.EmailAdress,newcontact->person_relax_info.EmailAdress);
	strcpy(pb->person_relax_info.ReferenceSocialNetwork,newcontact->person_relax_info.ReferenceSocialNetwork);
	strcpy(pb->person_relax_info.ReferenceMessage,newcontact->person_relax_info.ReferenceMessage);
}


void addPerson(PhoneBook *pb, PhoneBook *newcontact){
	
	if(current_count < MAX_PHONE_BOOK_LEN){
	
	findPerson(pb, newcontact);
	if(ind == -1){
		SwapInfo(&(pb[current_count]), newcontact);
		current_count += 1;
	}
	
	else{
		printf("Этот контакт уже существует! \n");
	}
	
	}
	
	else{
		printf("Phonebook underflow!!!");
	}
	
}

void deletePerson(PhoneBook *pb, PhoneBook *newcontact){
	if(current_count < 1){
		printf("You can't delete a contact because there's not one yet\n");
		return;
	}
	
	findPerson(pb, newcontact);
	if (ind == -1){
		printf("No contact yet...\n");
				
	}
	else{
		for (size_t i = ind; i < current_count ; ++i){
			SwapInfo(&(pb[i]), &(pb[i+1]));

		}
		current_count -= 1;
	}
}

void SetData(PhoneBook *pb){
	printf("Input data: \n");
	char fn[MAX_NAME_LEN];
	char ln[MAX_NAME_LEN];
	char fam[MAX_NAME_LEN];
	
	printf("Enter your first name: ");
	scanf("%19s",fn);
	printf("\nEnter your last name: ");
	scanf("%19s",ln);
	printf("\nEnter your ochestvo: ");
	scanf("%19s",fam);
	PersonInit(&(pb->person), fn, ln, fam);
	
	char job_adr[JOB_ADDRESS_LEN];
	char job_pos[POSITION_LEN];
	printf("\nEnter your job address: ");
	scanf("%29s",job_adr);
	printf("\nEnter your jop position: ");
	scanf("%29s",job_pos);
	PersonJobInfoInit(&(pb->person_job_info),job_adr, job_pos);
		
	char phone_number[PHONE_NUMBER_LEN];
	char email_adr[EMAIL_ADDRESS_LEN];
	char ref_social[REFERENCE_SOCIAL_NETWORK_LEN];
	char ref_msg[REFERENCE_MESSAGE_LEN];
	printf("\nEnter your phone number: ");
	scanf("%14s",phone_number);
	printf("\nEnter your email address: ");
	scanf("%19s",email_adr);
	printf("\nEnter your social reference: ");
	scanf("%29s",ref_social);
	printf("\nEnter your message reference: ");
	scanf("%29s",ref_msg);
	PersonRelaxInit(&(pb->person_relax_info),phone_number, email_adr,ref_social,ref_msg);
	
}

void updatePersonInfo(PhoneBook *pb, PhoneBook *newcontact, PhoneBook *updateContact){
	if(current_count < 1){
		printf("You can't update a contact because there's not one yet\n");
		return;
	}
	
	findPerson(pb, newcontact);
	
	if (ind == -1){
		printf("No contact yet...\n");
				
	}
	
	else{
		SwapInfo(&(pb[ind]), updateContact);
		
	}
}

void displayPhoneBook(PhoneBook *pb){
	if(current_count < 1){
		printf("You don't have any contacts yet\n");
		return;
	}
	for(size_t j = 0; j < current_count; ++j){
		printf("\nfirstname: %s, lastame: %s, ochestvo: %s\n", pb[j].person.firstName, pb[j].person.lastName, pb[j].person.famName);
		printf("job address: %s, job position: %s\n", pb[j].person_job_info.JobAddress, pb[j].person_job_info.Position);
		printf("phone number: %s, email address: %s, reference social network: %s, reference message: %s\n", pb[j].person_relax_info.PhoneNumber, pb[j].person_relax_info.EmailAdress,pb[j].person_relax_info.ReferenceSocialNetwork,pb[j].person_relax_info.ReferenceMessage);
	}
}