#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>

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
    if((semid=semget(IPC_PRIVATE,1,0666))==-1) dd_error("errore nella creazione del semaforo");
    union semun arg;
    arg.val=0;
    if(semctl(semid,0,SETVAL,arg)==-1) dd_error("errore nell'iniziallizazione");
    pid_t id_son=fork();
    if(id_son==0){
        if(reserveSem(semid)==-1) dd_error("errore semaforo non riservato");
        printf("il processo figlio con pid:%d è entrato nella sezione critica\n",getpid());
        fflush(stdout);
        //if(relaseSem(semid)==-1) dd_error("semaforo non rilasciato");
        exit(EXIT_SUCCESS);
    }
    sleep(id_son%10);
    printf("Il processo padre con pid:%d sta dando l'autorizzazione al processo figlio di entrare nella sezione critica,dopo aver atteso:%d secondi\n", getpid(),id_son%10);
    fflush(stdout);
    relaseSem(semid);
    wait(NULL);
    if(semctl(semid,0,IPC_RMID)==-1) dd_error("errore nella deallocazione del semaforo");
}