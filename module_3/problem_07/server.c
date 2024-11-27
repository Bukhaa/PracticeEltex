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
    mqd_t mq;
    struct message_text message, return_message;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct message_text);
    attr.mq_curmsgs = 0;

    if((mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0660, &attr)) == -1){
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    printf("Server start work\n");

    while (1) {
        
        if (mq_receive(mq, (char*)&return_message, sizeof(return_message), NULL) == -1) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }

        if (strcmp(return_message.buf, "exit") == 0)
            break;

        printf("Message received from client: %s\n\n", return_message.buf);

        printf("Please type a message: ");
        fgets(message.buf, BUF_SIZE, stdin);

        int length = strlen(message.buf);
        if (message.buf[length - 1] == '\n')
            message.buf[length - 1] = '\0';

        if (strcmp(message.buf, "exit") == 0) {
            mq_send(mq, (char*)&message, sizeof(message), 0);
            break;
        }

        if (mq_send(mq, (char*)&message, sizeof(message), 0) == -1) {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }
    }

    if (mq_close(mq) == -1) {
        perror("mq_close");
    }

    if (mq_unlink(QUEUE_NAME) == -1) {
        perror("mq_unlink");
    }

    printf("Bye\n");
    exit(EXIT_SUCCESS);
}
