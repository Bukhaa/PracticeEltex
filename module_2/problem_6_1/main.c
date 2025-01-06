#include<stdio.h>
#include "contact_list.h"
#include "dlist.h"


void test_1(){
	
	node* head = NULL;
    PhoneBook newContact1;
    PersonInit(&(newContact1.person), "sasha", "bukharov", "vladimirovich");
	PersonJobInfoInit(&(newContact1.person_job_info),"nstu", "student");
	PersonRelaxInit(&(newContact1.person_relax_info),"1234567", "sasha@mail.ru","-","@sashab");
	head = insert_sort(head, &newContact1); 
	
	PhoneBook newContact2;
    PersonInit(&(newContact2.person), "nikita", "emelyanov", "sergeevich");
	PersonJobInfoInit(&(newContact2.person_job_info),"nstu", "student");
	PersonRelaxInit(&(newContact2.person_relax_info),"89713311", "nikita@yandex.ru","@nikitae_1","-");
	head = insert_sort(head, &newContact2); 
	
	PhoneBook newContact3;
    PersonInit(&(newContact3.person), "egor", "alexeev", "maksimovich");
	PersonJobInfoInit(&(newContact3.person_job_info),"sibguti", "student");
	PersonRelaxInit(&(newContact3.person_relax_info),"1111111", "-","egor_m_1","egor_m_2");
	head = insert_sort(head, &newContact3); 
	
	
	print_dlist(head);
	
	clear(head);
}

void test_2(){
	
	node* head = NULL;
    PhoneBook newContact1;
    PersonInit(&(newContact1.person), "sasha", "bukharov", "vladimirovich");
	PersonJobInfoInit(&(newContact1.person_job_info),"nstu", "student");
	PersonRelaxInit(&(newContact1.person_relax_info),"1234567", "sasha@mail.ru","-","@sashab");
	head = insert_sort(head, &newContact1); 
	
	PhoneBook newContact2;
    PersonInit(&(newContact2.person), "nikita", "emelyanov", "sergeevich");
	PersonJobInfoInit(&(newContact2.person_job_info),"nstu", "student");
	PersonRelaxInit(&(newContact2.person_relax_info),"89713311", "nikita@yandex.ru","@nikitae_1","-");
	head = insert_sort(head, &newContact2); 
	
	PhoneBook newContact3;
    PersonInit(&(newContact3.person), "egor", "alexeev", "maksimovich");
	PersonJobInfoInit(&(newContact3.person_job_info),"sibguti", "student");
	PersonRelaxInit(&(newContact3.person_relax_info),"1111111", "-","egor_m_1","egor_m_2");
	head = insert_sort(head, &newContact3); 
	
	
	print_dlist(head);
	printf("\n");
	
	head = delete_contact(head, "bukharov");
	
	print_dlist(head);
	printf("\n");
	
	PhoneBook newContact4;
    PersonInit(&(newContact4.person), "petya", "yakimov", "nikolaevich");
	PersonJobInfoInit(&(newContact4.person_job_info),"itmo", "student");
	PersonRelaxInit(&(newContact4.person_relax_info),"9999999", "yakimov@yandex.ru","yakimov_ref_1","-");
	head = insert_sort(head, &newContact4);
	
	print_dlist(head);
	printf("\n");
	
	head = delete_contact(head, "alexeev");
	
	print_dlist(head);
	
	clear(head);
}

void test_3(){
	
	node* head = NULL;
    PhoneBook newContact1;
    PersonInit(&(newContact1.person), "sasha", "bukharov", "vladimirovich");
	PersonJobInfoInit(&(newContact1.person_job_info),"nstu", "student");
	PersonRelaxInit(&(newContact1.person_relax_info),"1234567", "sasha@mail.ru","-","@sashab");
	head = insert_sort(head, &newContact1); 
	
	PhoneBook newContact2;
    PersonInit(&(newContact2.person), "nikita", "emelyanov", "sergeevich");
	PersonJobInfoInit(&(newContact2.person_job_info),"nstu", "student");
	PersonRelaxInit(&(newContact2.person_relax_info),"89713311", "nikita@yandex.ru","@nikitae_1","-");
	head = insert_sort(head, &newContact2); 
	
	PhoneBook newContact3;
    PersonInit(&(newContact3.person), "egor", "alexeev", "maksimovich");
	PersonJobInfoInit(&(newContact3.person_job_info),"sibguti", "student");
	PersonRelaxInit(&(newContact3.person_relax_info),"1111111", "-","egor_m_1","egor_m_2");
	head = insert_sort(head, &newContact3); 
	
	print_dlist(head);
	printf("\n");
	
	PhoneBook newContactu;
    PersonInit(&(newContactu.person), "NIKITA", "EMELYANOV", "SERGEEVICH");
	PersonJobInfoInit(&(newContactu.person_job_info),"snsu", "student");
	PersonRelaxInit(&(newContactu.person_relax_info),"90909090", "-","-","nikita_ref_2");
	update(head,newContact2.person.lastName, &newContactu);
	
	print_dlist(head);
	printf("\n");
	
	PhoneBook newContact4;
    PersonInit(&(newContact4.person), "petya", "yakimov", "nikolaevich");
	PersonJobInfoInit(&(newContact4.person_job_info),"itmo", "student");
	PersonRelaxInit(&(newContact4.person_relax_info),"9999999", "yakimov@yandex.ru","yakimov_ref_1","-");
	head = insert_sort(head, &newContact4);
	
	print_dlist(head);
	printf("\n");
	
	head = delete_contact(head, "alexeev");
	
	print_dlist(head);
	
	clear(head);
}

int main(){
	
	printf("TEST #1_1:\n");
	test_1();
	printf("TEST #2_2:\n");
	test_2();
	printf("TEST #3_3:\n");
	test_3();
	
	return 0;
}

