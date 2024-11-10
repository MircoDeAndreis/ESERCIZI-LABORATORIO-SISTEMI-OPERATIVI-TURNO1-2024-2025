#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/msg.h>

struct mymsgN {
    long mtype;
    char mtext[256];
    pid_t pid;
};

int main(){
    int id;
    if((id=msgget(IPC_PRIVATE,0666))==-1){
        perror("coda non creata");
        exit(EXIT_FAILURE);
    }
    pid_t pid;
    if((pid=fork())==-1){
        perror("fork non avvenuta");
        exit(EXIT_FAILURE);
    }
    if(pid==0){ //processo figlio
        struct mymsgN messaggio;
        messaggio.mtype=1;
        strcpy(messaggio.mtext,"saluti da");
        messaggio.pid=getpid();
        if(msgsnd(id,&messaggio,sizeof(messaggio.mtext)+sizeof(messaggio.pid),IPC_NOWAIT)==-1){
            perror("messaggio non inviato");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }else{
        struct mymsgN messaggio;
        if(msgrcv(id,&messaggio,sizeof(messaggio.mtext)+sizeof(messaggio.pid),0,0)==-1){
            perror("messaggio non ricevuto");
            exit(EXIT_FAILURE);
        }
        printf("messaggio ricevuto dal figlio: %s\npid:%d\n",messaggio.mtext,messaggio.pid);
        if(msgctl(id,IPC_RMID,NULL)==-1){
            perror("coda non eliminata");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
}