#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include "./f_header.h"

int main(){
    char buffer[256];
    char* messaggio=malloc(1);
    while(fgets(buffer,256,stdin)!=NULL){
        char* temp=realloc(messaggio,(strlen(messaggio)+strlen(buffer))*sizeof(char));
        if(temp==NULL) dd_error("errore nella creazione del messaggio");
        messaggio=temp;
        messaggio=strcat(messaggio,buffer);
    }
    int shmid,semid;
    if((semid=semget(SEMKEY,2,IPC_CREAT|0666))==-1) dd_error("errore nella creazione del semaforo");
    //iniziallizzazione del semaforo
    //pause(); //forzare il context switch
    union semun arg;
    unsigned short sem[2]={1,0};
    arg.array=sem;
    if(semctl(semid,0,SETALL,arg)==-1) dd_error("errore nell'inizializzazione del semaforo");
    //sincronizzazione con altro processo
    struct sembuf sem_op;
    sem_op.sem_flg=0;
    sem_op.sem_num=READ;
    sem_op.sem_op=0;
    if(semop(semid,&sem_op,1)==-1) dd_error("errore nella modifica del semop");
    //fine sincronizzazione
    if((shmid=shmget(SHKEY,strlen(messaggio)+1,IPC_CREAT|0666))==-1) dd_error("errore nella creazione della memoria"); //creazione della memoria
    char* mem_condivisa;
    if((mem_condivisa=shmat(shmid,NULL,0))==(void*)-1) dd_error("errore nell'attacco della memoria");
    sem_op.sem_flg=0;
    sem_op.sem_num=WRITE;
    sem_op.sem_op=-1;
    if(semop(semid,&sem_op,1)==-1) dd_error("errore nel decremento del semaforo");//entrare nell'area riservata
    strcpy(mem_condivisa,messaggio);
    sem_op.sem_flg=0;
    sem_op.sem_num=READ;
    sem_op.sem_op=1;
    printf("[scrittore] : inviati %lu bytes\n",strlen(messaggio)+1);
    if(semop(semid,&sem_op,1)==-1) dd_error("errore nell'incremento del semaforo");//permette al read di accedere alla memoria
    sem_op.sem_flg=0;
    sem_op.sem_num=WRITE;
    sem_op.sem_op=-1;
    if(semop(semid,&sem_op,1)==-1) dd_error("errore nel decremento del semaforo");//aspetto la fine del processo read per eliminare la memoria
    if(semctl(semid,0,IPC_RMID)==-1) dd_error("errore nella cancellazione del semaforo");//rimuovo semaforo
    if(shmctl(shmid,IPC_RMID,NULL)==-1) dd_error("errore nella distruzione del semaforo");//rimuovo memoria
}


