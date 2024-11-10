#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/msg.h>
#include"f_header.h"

void maiuscolo(char* string){
    for(int i=0;string[i]!='\n' && string[i]!='\0' && string[i]!='\t';i++){
        string[i]=toupper(string[i]);
    }
}

int main(){
    int server_id;
    if((server_id=msgget(KEYFORSERVER,IPC_CREAT|0666))==-1){
        perror("errore nella creazione della coda del server");
        exit(EXIT_FAILURE);
    }
    while(1){
        struct mymsgN messaggio;
        if(msgrcv(server_id,&messaggio,sizeof(messaggio.mtext),0,0)==-1){
            perror("errore nella ricezione del messaggio");
            exit(EXIT_FAILURE);
        }
        if(messaggio.mtype==1){
            if(msgctl(server_id,IPC_RMID,NULL)==-1){
                perror("chiusura coda client fallita");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        pid_t pid=fork();
        if(pid==0){//processo figlio
            maiuscolo(messaggio.mtext);
            if(msgsnd(messaggio.mtype,&messaggio,sizeof(messaggio.mtext),0)==-1){
                perror("messaggio non inviato al client");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
    }
}