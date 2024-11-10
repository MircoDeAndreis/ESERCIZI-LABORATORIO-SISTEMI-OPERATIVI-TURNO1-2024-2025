#include <stdio.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>


void dd_error(char* error){
    perror(error);
    exit(1);
}

int reserveSem(int semid){
    struct sembuf sops;
    sops.sem_flg=0;
    sops.sem_op=-1;
    sops.sem_num=0;
    return semop(semid,&sops,1);
}


int relaseSem(int semid){
    struct sembuf sops;
    sops.sem_flg=0;
    sops.sem_op=1;
    sops.sem_num=0;
    return semop(semid,&sops,1);
}

int main(){
    int semid;
    if((semid=semget(IPC_PRIVATE,1,0666))==-1) dd_error("semaforo non creato");
    union semun arg;
    arg.val=0;
    if(semctl(semid,0,SETVAL,arg)==-1) dd_error("errore nell'inizializzazione");
    if(fork()==0){//figlio 
        sleep(5);
        if(relaseSem(semid)==-1) dd_error("errore nel rilascio del semaforo");
        printf("Il figlio con pid:%d, è terminato dopo aver atteso 5 secondi\n",getpid());
        fflush(stdout);
        exit(EXIT_SUCCESS);
    }else{
        if(reserveSem(semid)==-1) dd_error("errore semaforo non riservato");
        if(semctl(semid,0,IPC_RMID)==-1) dd_error("errore nella deallocazione del semaforo");
        printf("Il padre con pid:%d, è terminato dopo aver atteso la fine del figlio\n",getpid());
        fflush(stdout);
        exit(EXIT_SUCCESS);
    }
}