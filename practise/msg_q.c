#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 1234

typedef struct msgbuf {
    long mtype;
    char mtext[100];
} msgbuf_t;

int main() 
{
    int msgid;
    struct msgbuf message;
	
    /*msgid => handle to you message Q
     * MSG_KEY => id to identify the queue
     * 0666 | IPC_CREATE, permissions and create doesnt exits*/

    /*If another process uses the same MSG_KEY?? will it not 
     * access the same queue?? Yes. that why instead of hardcoded 
     * MSG_KEY we generate a key using 
     *
     *	key_t msg_key = ftok(\"random_file_name\", 65)
     *	
     *	and then use in 
     *	
     *	msgid = msgget(msg_key, 0666 | IPC_CREAT);
     *
     * read man 3 ftok for details
     */



    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message Queue created (id=%d).\n", msgid);

    message.mtype = 1;
    strcpy(message.mtext, "Hello via Message Queue!");
	
    /*send to msg queue using handle Q*/
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Sent: %s\n", message.mtext);
    
    /*receive from msg queue using handle Q*/
    if (msgrcv(msgid, &message, sizeof(message.mtext), 1, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }

    printf("Received: %s\n", message.mtext);
	

    /*used the queue now delete it */
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    printf("Message queue deleted.\n");

    return 0;
}

