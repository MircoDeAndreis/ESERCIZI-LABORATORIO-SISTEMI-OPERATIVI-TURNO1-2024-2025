#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/msg.h>
#include"f_header.h"

int main(int argc,char* argv[]){
    for(int i=1;i<argc;i++){
        pid_t pid;
        if((pid=fork())==-1){
            perror("fork non avvenuta");
            exit(EXIT_FAILURE);
        }
        if(pid==0){//processo figlio
            int id;
            if((id=msgget(getpid(),IPC_CREAT|0666))==-1){//al posto di ipc_private posso utilizzare il pid del processo
                perror("coda non creata");
                exit(EXIT_FAILURE);
            }
            struct mymsgN messaggio;
            messaggio.mtype=id;
            strcpy(messaggio.mtext,argv[i]);
            int server_id;
            if((server_id=msgget(KEYFORSERVER,0))==-1){
                perror("fallimento nel collegamento al server");
                exit(EXIT_FAILURE);
            }
            if(msgsnd(server_id,&messaggio,sizeof(messaggio.mtext),0)==-1){
                perror("messaggio non inviato");
                exit(EXIT_FAILURE);
            }
            if(msgrcv(id,&messaggio,sizeof(messaggio.mtext),0,0)==-1){
                perror("messaggio non ricevuto");
                exit(EXIT_FAILURE);
            }
            printf("Figlio numero %d con pid %d, ha ricevuto questo messaggio dal server:%s\n",i,getpid(),messaggio.mtext);
            fflush(stdout);
            if(msgctl(id,IPC_RMID,NULL)==-1){
                perror("chiusura coda client fallita");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
    }
    while(wait(NULL)!=-1);
    struct mymsgN messaggio;
    messaggio.mtype=1; //segnale per comunicare al server di interrompere le comunicazioni
    int server_id;
    if((server_id=msgget(KEYFORSERVER,0))==-1){
        perror("fallimento nel collegamento al server");
        exit(EXIT_FAILURE);
    }
    if(msgsnd(server_id,&messaggio,sizeof(messaggio.mtext),0)==-1){
        perror("messaggio non inviato");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}