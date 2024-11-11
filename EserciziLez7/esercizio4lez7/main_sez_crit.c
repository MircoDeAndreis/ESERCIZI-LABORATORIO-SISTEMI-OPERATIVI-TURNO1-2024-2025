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
    arg.val=1;
    if(semctl(semid,0,SETVAL,arg)==-1) dd_error("errore nell'iniziallizazione");
    char* sez[3]={"figlio1","figlio2","figlio3"};
    for(int i=0;i<3;i++){
        if(fork()==0){
            if(reserveSem(semid)==-1) dd_error("errore semaforo non riservato");
            printf("il figlio numero:%d con pid:%d,ha stampato:%s\n",i+1,getpid(),sez[i]);
            fflush(stdout);
            if(relaseSem(semid)==-1) dd_error("semaforo non rilasciato");
            exit(EXIT_SUCCESS);
        }
    }
    while(wait(NULL)!=-1);
    if(semctl(semid,0,IPC_RMID)==-1) dd_error("errore nella diallocazione del semaforo");
    printf("il padre con pid:%d,termina con successo dopo aver deallocato il semaforo\n",getpid());
    exit(EXIT_SUCCESS);
}