#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>
#include "f_header.h"

void codice_da_eseguire(){
    printf("Linux\n");
    fflush(stdout);
}

int main(){
    int semid;
    if((semid=semget(keysem,1,IPC_CREAT|IPC_EXCL|0666))!=-1){//il processo ha creato il semaforo ed è il proprietario
        union semun arg;
        arg.val=0;
        if(semctl(semid,0,SETVAL,arg.val)==-1){ //viene iniziallizato a arg.val il semaforo 0 del set id
            dd_error("semaforo non inizializzato");
        }
        struct sembuf sop;
        //sem_otime viene modificato solo dopo che la funzione semop termina quindi è necessaria una chiamata semop fasulla
        sop.sem_num=0;
        sop.sem_op=0;
        sop.sem_flg=0;
        if(semop(semid,&sop,1)==-1) dd_error("errore nell'inizializzazione");
        sop.sem_num=0;
        sop.sem_op=-1;
        sop.sem_flg=0;
        if(semop(semid,&sop,1)==-1) dd_error("errore nell'inizializzazione");
        codice_da_eseguire();
        printf("Processo sbloccato con PID: %d\n", getpid());
        fflush(stdout);
        if(semctl(semid,0,IPC_RMID)==-1) dd_error("semaforo non deallocato");
        exit(EXIT_SUCCESS);
    }else{//il processo non ha creato il semaforo
        if((semid=semget(keysem,1,0666))==-1) dd_error("errore nella creazione del semaforo");
        //il semaforo esiste
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
        struct sembuf sop;
        sop.sem_num=0;
        sop.sem_op=1;
        sop.sem_flg=0;
        if(semop(semid,&sop,1)==-1){
            dd_error("errore nell'inizializzazione");
        }
        codice_da_eseguire();
        printf("Processo terminato con pid:%d\n",getpid());
        fflush(stdout);
        exit(EXIT_SUCCESS);
    }
}