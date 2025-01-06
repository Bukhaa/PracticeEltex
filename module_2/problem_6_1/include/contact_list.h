#include<stdio.h>

#define MAX_NAME_LEN 20 
#define JOB_ADDRESS_LEN 30
#define POSITION_LEN 30
#define PHONE_NUMBER_LEN 15
#define EMAIL_ADDRESS_LEN 20
#define REFERENCE_SOCIAL_NETWORK_LEN 30
#define REFERENCE_MESSAGE_LEN 30
#define MAX_PHONE_BOOK_LEN 100

typedef struct Person{
	
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];
	char famName[MAX_NAME_LEN];
	
	
}Person;

typedef struct PersonJobInfo{
	
	char JobAddress[JOB_ADDRESS_LEN];
	char Position[POSITION_LEN];
	
}PersonJobInfo;

typedef struct PersonRelaxInfo{
	
	char PhoneNumber[PHONE_NUMBER_LEN];
	char EmailAdress[EMAIL_ADDRESS_LEN];
	char ReferenceSocialNetwork[REFERENCE_SOCIAL_NETWORK_LEN];
	char ReferenceMessage[REFERENCE_MESSAGE_LEN];
	
}PersonRelaxInfo;

typedef struct PhoneBook{
	
	Person          person;
	PersonJobInfo   person_job_info;
	PersonRelaxInfo person_relax_info;
	
}PhoneBook;

void PersonInit(Person *p, char* fn, char* ln, char* fam);
void PersonJobInfoInit(PersonJobInfo *p, char* adr, char* pos);
void PersonRelaxInit(PersonRelaxInfo *p, char* phone, char* email, char* ref_soc, char* ref_msg);
void findPerson(PhoneBook *pb, PhoneBook *newcontact);
void SwapInfo(PhoneBook *pb, PhoneBook *newcontact);
void addPerson(PhoneBook *pb, PhoneBook *newcontact);
void deletePerson(PhoneBook *pb, PhoneBook *newcontact);
void SetData(PhoneBook *pb);
void updatePersonInfo(PhoneBook *pb, PhoneBook *newcontact, PhoneBook *updateContact);
void displayPhoneBook(PhoneBook *pb);