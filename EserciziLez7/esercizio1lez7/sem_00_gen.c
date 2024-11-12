#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>
#include "f_header.h"



int main(){
    int semid;
    if((semid=semget(keysem,1,IPC_CREAT|IPC_EXCL|0666))==-1){
        dd_error("semaforo non creato correttamente");
    }
    //pause(); //nel caso si voglia simulare un context switch per far vedere il problema di sincronizzazione
    union semun arg;
    arg.val=0;
    if(semctl(semid,0,SETVAL,arg)==-1){ //viene iniziallizato a arg.val il semaforo 0 del set semid
        dd_error("semaforo non inizializzato");
    }
    struct sembuf sop;
    sop.sem_num=0;
    sop.sem_op=0;
    sop.sem_flg=0;
    if(semop(semid,&sop,1)==-1){
        dd_error("errore nell'inizializzazione");
    }
    exit(EXIT_SUCCESS);
}
