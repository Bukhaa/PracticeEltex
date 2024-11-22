#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SERVER_KEY_PATHNAME "q_file"
#define PROJECT_ID 'a'
#define BUF_SIZE 200

struct message_text {
    char buf[BUF_SIZE];
};

struct message {
    long message_type;
    struct message_text message_text;
};

int main(int argc, char **argv) {
    key_t server_queue_key;
    int server_qid;
    struct message my_message, return_message;

    if ((server_queue_key = ftok(SERVER_KEY_PATHNAME, PROJECT_ID)) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    if ((server_qid = msgget(server_queue_key, 0)) == -1) {
        perror("msgget: server_qid");
        exit(EXIT_FAILURE);
    }

   my_message.message_type = 1;  

    printf("Please type a message: ");

    while (1) {
	
	fgets(my_message.message_text.buf, BUF_SIZE, stdin);
        int length = strlen(my_message.message_text.buf);
        if (my_message.message_text.buf[length - 1] == '\n')
            my_message.message_text.buf[length - 1] = '\0';

        if (strcmp(my_message.message_text.buf, "exit") == 0) {
            msgsnd(server_qid, &my_message, sizeof(struct message_text), 0);
            break;
        }

        if (msgsnd(server_qid, &my_message, sizeof(struct message_text), 0) == -1) {
            perror("client: msgsnd");
            exit(EXIT_FAILURE);
        }

        if (msgrcv(server_qid, &return_message, sizeof(struct message_text), 2, 0) == -1) {
            perror("client: msgrcv");
            exit(EXIT_FAILURE);
        }

	if (strcmp(return_message.message_text.buf, "exit") == 0) 
		break;
        

        printf("Message received from server: %s\n\n", return_message.message_text.buf);
        printf("Please type a message: ");
    }
    
    printf("Bye\n");
    exit(EXIT_SUCCESS);
}

