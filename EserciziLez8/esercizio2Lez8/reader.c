#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include "./f_header.h"

int main(){
    int semid;
    if((semid=semget(SEMKEY,1,0666))==-1) dd_error("errore nella creazione del semaforo");
    union semun arg;
    struct semid_ds ds;
    arg.buf=&ds;
    for (int j = 0; j < MAX_TRIES; ++j) {
        if (semctl(semid, 0, IPC_STAT, arg) == -1)
            dd_error("errorre nella copia della struttura");
        if (ds.sem_otime != 0) // è stata eseguita Semop()?
            break; // sì, usciamo dal ciclo
        sleep(1); // diversamente, attendiamo e ritentiamo
    }
    if (ds.sem_otime == 0) dd_error("semaforo non inizializzato");
    int shmid;
    if((shmid=shmget(SHKEY,0,0666))==-1) dd_error("memoria non inizializzato");
    char* messaggio;
    if((messaggio=(char*)shmat(shmid,NULL,0))==(void*)-1) dd_error("errore nell'attacco della memoria");
    struct sembuf sem_op;
    sem_op.sem_flg=0;
    sem_op.sem_num=READ;
    sem_op.sem_op=-1;
    if(semop(semid,&sem_op,1)==-1) dd_error("errore nella sincronizzazione");
    printf("[lettore] : ricevuti %lu bytes\n",strlen(messaggio)+1);
    printf("Il messaggio ricevuto da reader con pid:%d è:%s\n",getpid(),messaggio);
    sem_op.sem_flg=0;
    sem_op.sem_num=WRITE;
    sem_op.sem_op=1;
    if(semop(semid,&sem_op,1)==-1) dd_error("errore nella sincronizzazione");
}