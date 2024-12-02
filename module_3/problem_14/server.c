#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void init_servaddr(struct sockaddr_in *servaddr){
    	
    servaddr->sin_family = AF_INET; // семейство адресов
    servaddr->sin_addr.s_addr = INADDR_ANY; // айпи адрес 
    servaddr->sin_port = htons(PORT); // номер порта  	
}

int main() {
    int sockfd;
    char buffer_rec[BUFFER_SIZE];
    char buffer_snd[BUFFER_SIZE];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
	perror("socket failed!\n");
	exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    init_servaddr(&servaddr);

    if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0){
	perror("server bind failed!\n");
	exit(EXIT_FAILURE);
    }
    len = sizeof(cliaddr);

    printf("Server start work!\n");
    while (1) {

        int n = recvfrom(sockfd, buffer_rec, BUFFER_SIZE, 0, (struct sockaddr *)&cliaddr, &len); 
	if(n < 0){
	   perror("recvform failed!\n");
	   exit(EXIT_FAILURE);
	}

        buffer_rec[n] = '\0';
        printf("Клиент отправил: %s\n", buffer_rec);
	
	printf("Сервер отвечает: ");
	fgets(buffer_snd, BUFFER_SIZE, stdin);

        if((sendto(sockfd, buffer_snd, strlen(buffer_snd), 0, (const struct sockaddr *)&cliaddr, len)) < 0){
	   perror("sendto failed!\n");
	   exit(EXIT_FAILURE);
	}
    }

    if(close(sockfd) == -1){
	perror("close socked failed!\n");
	exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

