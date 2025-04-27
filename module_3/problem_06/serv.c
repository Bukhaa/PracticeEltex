#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define SERVER_KEY_PATHNAME "./read.me"
#define PROJECT_ID 'a'
#define QUEUE_PERMISSIONS 0660
#define BUF_SIZE 200

struct message {
    long message_type;
    char message_text[BUF_SIZE];
};

int main(int argc, char **argv) {
    key_t msg_queue_key;
    int qid;
    struct message message;
    struct message return_message;

    if ((msg_queue_key = ftok(SERVER_KEY_PATHNAME, PROJECT_ID)) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    if ((qid = msgget(msg_queue_key, IPC_CREAT | QUEUE_PERMISSIONS)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    
    message.message_type = 2;
    printf("Server start work\n");

    while (1) {
        if (msgrcv(qid, &return_message, sizeof(message.message_text), 1, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        if (strcmp(return_message.message_text, "exit") == 0)
		break;
        

        printf("Message received from client: %s\n\n", return_message.message_text);
 
        printf("Please type a message: ");
        fgets(message.message_text, BUF_SIZE, stdin);

	int length = strlen(message.message_text);
        if (message.message_text[length - 1] == '\n')
            message.message_text[length - 1] = '\0';

        if (strcmp(message.message_text, "exit") == 0) {
            msgsnd(qid, &message, sizeof(message.message_text), 0);
            break;
        }


        if (msgsnd(qid, &message, sizeof(message.message_text), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
    }

    if (msgctl(qid, IPC_RMID, NULL) == -1) {
        perror("server: msgctl");
        exit(EXIT_FAILURE);
    }
    
    printf("Bye\n");
    exit(EXIT_SUCCESS);
}

