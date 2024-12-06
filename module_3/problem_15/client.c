#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define str1 "Enter 1 parametr:\n"
#define str2 "Enter 2 parametr:\n" 
#define str3 "Choose the operation:\n"         

void error(const char *msg){
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){
    int my_sock, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buff[1024];
    printf("TCP DEMO CLIENT\n");
	
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(EXIT_FAILURE);
    }
    
   portno = atoi(argv[2]);
    
   my_sock = socket(AF_INET, SOCK_STREAM, 0);
   if (my_sock < 0) 
      error("ERROR opening socket");
    
   server = gethostbyname(argv[1]);
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(EXIT_FAILURE);
   }

   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   
   serv_addr.sin_port = htons(portno);
    
   if (connect(my_sock,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
      error("ERROR connecting");
	
   while (1){

      if((n = recv(my_sock, &buff[0], sizeof(buff) - 1, 0)) < 0){
         perror("recv failed!\n");
	 exit(EXIT_FAILURE);
      }
         
      printf("S=>C:%s\n", buff);

      if((strcmp(buff, str1) == 0) || (strcmp(buff, str2) == 0) || (strcmp(buff, str3) == 0)){
	 buff[n] == '\0';
         
         printf("S<=C:"); 
	 fgets(&buff[0], sizeof(buff) - 1, stdin);
         send(my_sock, &buff[0], strlen(&buff[0]), 0);
      }
	else
	   break;
   } 
     
     close(my_sock);
     exit(EXIT_SUCCESS);
	
}
