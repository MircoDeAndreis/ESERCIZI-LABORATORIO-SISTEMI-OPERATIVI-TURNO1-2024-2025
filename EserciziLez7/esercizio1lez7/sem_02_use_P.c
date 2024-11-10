#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>
#include "f_header.h"



int main(){
    int semid;
    if((semid=semget(keysem,1,0666))==-1){
        dd_error("semaforo non esiste");
    }
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
    struct sembuf sops;
    sops.sem_num=0; 
    sops.sem_op=P; 
    sops.sem_flg=0;
    if(semop(semid,&sops,1)==-1) dd_error("operazione non effettuata");
    exit(EXIT_SUCCESS);
}