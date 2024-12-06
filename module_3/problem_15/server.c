/* Пример простого TCP сервера
   Порт является аргументом, для запуска сервера неободимо ввести:
   # ./[имя_скомпилированного_файла] [номер порта]
   # ./server 57123
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define str1 "Enter 1 parametr:\n"
#define str2 "Enter 2 parametr:\n" 
#define str3 "Choose the operation:\n"

void dostuff(int);

void error(const char *msg);

int nclients = 0;

void printusers();

int sum(int a, int b){
   return a+b;
}

int sub(int a, int b){
   return a-b;
}

int mult(int a, int b){
   return a*b;
}

int divis(int a, int b){
   return a/b;
}

int main(int argc, char *argv[]){
    char buff[1024];    
    printf("TCP SERVER DEMO\n");
	
    int sockfd, newsockfd;
    int portno; 
    int pid; 
    socklen_t clilen; 
    struct sockaddr_in serv_addr, cli_addr; 
	
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(EXIT_FAILURE);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) 
       error("ERROR opening socket");
	 
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
       error("ERROR on binding");
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
	
	
	    
    while (1) {
         newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0) 
             error("ERROR on accept");

	 nclients++; 
		
	 printusers();
		
         pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0){
             close(sockfd);
             dostuff(newsockfd);
             exit(EXIT_SUCCESS);
         }
         else close(newsockfd);
    }

    close(sockfd);
    exit(EXIT_SUCCESS); 
}

void dostuff (int sock){
	int bytes_recv;
	int a,b,r;
	char buff[20 * 1024];
	char operation;  

	memset(buff,0,sizeof(buff));

        write(sock, str1, sizeof(str1));
   
	bytes_recv = read(sock,&buff[0],sizeof(buff));
	if (bytes_recv < 0) error("ERROR reading from socket");
	a = atoi(buff);
	
	write(sock,str2,sizeof(str2));
	
	bytes_recv = read(sock,&buff[0],sizeof(buff));
	if (bytes_recv < 0) error("ERROR reading from socket");
	b = atoi(buff);
	
	write(sock,str3,sizeof(str3));
	bytes_recv = read(sock,&operation,sizeof(operation));
	if (bytes_recv < 0) error("ERROR reading from socket");
	
	switch(operation){
		case '+':
		   r = sum(a,b);
		   break;

		case '-':
		   r = sub(a,b);
		   break;

		case '*':
		   r = mult(a,b);
		   break;

		case '/':
		   r = divis(a,b);
		   break;

		default:
		   printf("Invalid operation!\n");
		   return;
	}
	
	snprintf(buff, sizeof(buff), "%d", r);
	buff[strlen(buff)] = '\n'; 
        	
	write(sock,&buff[0],sizeof(buff));
	 
	nclients--; 
    	printf("-disconnect\n"); 
	printusers();
	return;
}

void error(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void printusers(){
   if(nclients)
      printf("%d user on-line\n",nclients);
   else
      printf("No User on line\n");
}

