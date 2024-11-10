#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<math.h>
#include<sys/types.h>
#include<sys/msg.h>
#include"f_header.h"
#include<sys/sem.h>

int main(){
    int id;
    if((id=msgget(MYKEY,IPC_CREAT|0666))==-1){
        perror("coda di messaggi non creata");
        exit(EXIT_FAILURE);
    }
    /* non funziona perchè questo programma non ha i privilegi da root
    struct msqid_ds msgds;
    if(msgctl(id, IPC_STAT, &msgds) == -1){
        perror("struttura non copiata");
        exit(EXIT_FAILURE);
    }
    msgds.msg_qbytes = 8196; 
    if(msgctl(id, IPC_SET, &msgds) == -1){
        perror("struttura non modificata");
        exit(EXIT_FAILURE);
    }
    */
    printf("Inserire un messaggio che si vuole inviare con la seguente formattazione (numero intero stringa da volere inviare) per terminare la richiesta inserire -1 come campo intero:");
    fflush(stdout);
    while (1){
        char buffer[256];
        fgets(buffer,256,stdin);
        int i=0;
        for(;buffer[i]!=' ';i++);
        buffer[i]='\0';
        struct mymsgN messaggio;
        messaggio.mtype=atoi(buffer);
        if(messaggio.mtype==-1) break;
        strcpy(messaggio.mtext,&buffer[i+1]);
        if(msgsnd(id,&messaggio,sizeof(messaggio.mtext),IPC_NOWAIT)==-1){//con IPC_NOWAIT non rimane in attesa
            perror("messaggio non inviato");
            exit(EXIT_FAILURE);
        }
        printf("inserire nuovo messaggio (per terminare inserire -1 e stop nel campo stringa):");
        fflush(stdout);
    }
    if(msgctl(id,IPC_RMID,NULL)==-1){
        perror("coda di messaggi non eliminata");
        exit(EXIT_FAILURE);
    }
}