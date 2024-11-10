#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/msg.h>
#include <time.h>

struct mymsgN {
    long mtype;
    char mtext[100];
};

int main(){
    int id;
    if((id=msgget(IPC_PRIVATE,0666))==-1){
        perror("creazione della coda fallita");
        exit(EXIT_FAILURE);
    }
    struct msqid_ds msgds;
    if(msgctl(id,IPC_STAT,&msgds)==-1){
        perror("struttura non copiata");
        exit(EXIT_FAILURE);
    }
    printf("dimensione coda:%lu\nnumero di messaggi in coda:%lu\nultimo mesaggio inviato alle ore:%s", msgds.msg_qbytes, msgds.msg_qnum, ctime(&msgds.msg_stime));
    struct mymsgN messaggio;
    messaggio.mtype=1;
    strcpy(messaggio.mtext, "ciao");
    if (msgsnd(id, &messaggio, sizeof(messaggio.mtext), 0) == -1) {
        perror("msgsnd failed");
        exit(EXIT_FAILURE);
    }
    if(msgctl(id,IPC_STAT,&msgds)==-1){
        perror("struttura non copiata");
        exit(EXIT_FAILURE);
    }
    printf("ultimo mesaggio inviato alle ore:%s",ctime(&msgds.msg_stime));
    if(msgctl(id,IPC_RMID,NULL)==-1){
        perror("fallimento nella chiusura della coda");
        exit(EXIT_FAILURE);
    }
}   