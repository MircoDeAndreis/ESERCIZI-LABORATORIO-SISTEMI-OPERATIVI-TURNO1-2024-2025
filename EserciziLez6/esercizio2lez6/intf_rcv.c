#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/msg.h>
#include"f_header.h"

int main(){
    int id;
    if((id=msgget(MYKEY,0))==-1){
        perror("la coda non esiste");
        exit(EXIT_FAILURE);
    }
    int mtype=0;
    printf("Inserisci il tipo di messaggi da ricevere (0 per tutti i messaggi, un intero positivo per un tipo specifico): ");
    fscanf(stdin,"%d",&mtype);
    struct mymsgN messaggio;
    int i=1;
    while(msgrcv(id,&messaggio,sizeof(messaggio.mtext),mtype,IPC_NOWAIT)!=-1){
        printf("%d messaggio di tipo %ld: %s\n",i,messaggio.mtype,messaggio.mtext);
        i++;
    }
    if(msgctl(id,IPC_RMID,NULL)==-1){
        perror("coda di messaggi non eliminata");
        exit(EXIT_FAILURE);
    }
}