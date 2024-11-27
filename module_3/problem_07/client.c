#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <unistd.h>

#define QUEUE_NAME "/my_queue"
#define BUF_SIZE 200

struct message_text {
    char buf[BUF_SIZE];
};

int main(int argc, char **argv) {
    mqd_t server_mq;
    struct message_text my_message, return_message;

   if((server_mq = mq_open(QUEUE_NAME, O_RDWR)) == -1){
        perror("mq_open: server_mq");
        exit(EXIT_FAILURE);
    }

    printf("Please type a message: ");

    while (1) {
        fgets(my_message.buf, BUF_SIZE, stdin);
        int length = strlen(my_message.buf);
        if (my_message.buf[length - 1] == '\n')
            my_message.buf[length - 1] = '\0';

        if (strcmp(my_message.buf, "exit") == 0) {
            mq_send(server_mq, (char*)&my_message, sizeof(my_message), 0);
            break;
        }

        if (mq_send(server_mq, (char*)&my_message, sizeof(my_message), 0) == -1) {
            perror("client: mq_send");
            exit(EXIT_FAILURE);
        }

        if (mq_receive(server_mq, (char*)&return_message, sizeof(return_message), NULL) == -1) {
            perror("client: mq_receive");
            exit(EXIT_FAILURE);
        }

        if (strcmp(return_message.buf, "exit") == 0) 
            break;

        printf("Message received from server: %s\n\n", return_message.buf);
        printf("Please type a message: ");
    }
    
    if (mq_close(server_mq) == -1) {
        perror("mq_close");
    }

    printf("Bye\n");
    exit(EXIT_SUCCESS);
}
