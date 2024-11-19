#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#define DATASZ 256
#define MYKEY 0x1234

typedef struct my_data {
int counter;
char stringa[DATASZ];
} data;

void dd_error(char* error){
    perror(error);
    exit(1);
}


int main(){
    int shmid;
    if((shmid=shmget(MYKEY,sizeof(struct my_data),IPC_CREAT|0666))==-1) dd_error("errore nella creazione della memoria");
    struct my_data* messaggio;
    if((messaggio=(struct my_data*)shmat(shmid,NULL,0))==(void*)-1) dd_error("errore nel collgamento della memoria");
    strcpy(messaggio->stringa,"HELLO WORLD");
    messaggio->counter=0;
    if(shmdt(messaggio)==-1) dd_error("errore nel distacco");
    if(fork()==0){
        //if((shmid=shmget(MYKEY,sizeof(struct my_data),IPC_CREAT|0666))==-1) dd_error("errore nella creazione della memoria"); //non serve perchè l'id è univoco ed è già salvato in shmid
        if((messaggio=(struct my_data*)shmat(shmid,NULL,0))==(void*)-1) dd_error("errore nel collgamento della memoria"); //necessario perchè il processo figlio non è attaccato
        printf("Counter:%d\nMessage:%s\n",messaggio->counter,messaggio->stringa);
        fflush(stdout);
        //if(shmdt(messaggio)==-1) dd_error("errore nel distacco"); //opzinale perchè avviene in automatica alla terminazione del processo
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    if(shmctl(shmid,IPC_RMID,NULL)==-1) dd_error("errore nella deallocazione della memoria");
}
