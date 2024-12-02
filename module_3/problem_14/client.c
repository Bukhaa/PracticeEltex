#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void init_servaddr(struct sockaddr_in *servaddr, struct in_addr *addr){

    servaddr->sin_family = AF_INET; // семейство адресов
    if(servaddr->sin_addr.s_addr = inet_aton("127.0.0.1", addr) <= 0){
	perror("Неправильный адрес или неккоректный адрес!\n");
        exit(EXIT_FAILURE);
    } // айпи пк 192.168.1.36

    servaddr->sin_port = htons(PORT); // номер порта    
}

int main() {
    int sockfd;
    char buffer_rec[BUFFER_SIZE];
    char buffer_snd[BUFFER_SIZE];
    struct sockaddr_in servaddr;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
	perror("socket creation failed!\n");
	exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    struct in_addr addr;
    init_servaddr(&servaddr, &addr);
    int len = sizeof(servaddr);

    printf("Client start work!\n");
    while (1) {

        printf("Введите сообщение: ");
        fgets(buffer_snd, BUFFER_SIZE, stdin);

        if((sendto(sockfd, buffer_snd, strlen(buffer_snd), 0, 
	(const struct sockaddr *)&servaddr, len)) < 0) {
	       	perror("sendto failed!\n");
	        exit(EXIT_FAILURE);
	}

        int n = recvfrom(sockfd, buffer_rec, BUFFER_SIZE, 0, NULL, NULL);
	if(n < 0){
	   perror("recvfrom failed!\n");
	   exit(EXIT_FAILURE);
	}

        buffer_rec[n] = '\0';
        printf("Сервер ответил: %s\n", buffer_rec);
    }

    if(close(sockfd) == -1){
        perror("close socked failed!\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

