#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>
#include "f_header.h"



int main(){
    int semid;
    if((semid=semget(keysem,1,0666))==-1){
        dd_error("semaforo non creato correttamente");
    }
    if(semctl(semid,0,IPC_RMID,NULL)==-1){ //viene iniziallizato a arg.val il semaforo 0 del set id
        dd_error("semaforo non inizializzato");
    }
    exit(EXIT_SUCCESS);
}
