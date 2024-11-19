#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <time.h>

#define N 10
#define M 10

void dd_error(char* error){
    perror(error);
    exit(1);
}

int main(){
    int shmid,semid;
    if((semid=semget(IPC_PRIVATE,1,0666))==-1) dd_error("errore nella creazione del semaforo");//creazione semaforo
    union semun arg;
    arg.val=1;
    if(semctl(semid,0,SETVAL,arg)==-1) dd_error("errore nell'inizializzazione del semaforo");
    if((shmid=shmget(IPC_PRIVATE,sizeof(pid_t),0666))==-1) dd_error("errore nella creazione della memoria");
    pid_t* messaggio;
    if((messaggio=(pid_t*)shmat(shmid,NULL,0))==(void*)-1) dd_error("errore nell'attacco alla memoria");
    for(int i=0;i<N;i++){
        if(fork()==0){//processo figlio
            if((messaggio=(pid_t*)shmat(shmid,NULL,0))==(void*)-1) dd_error("errore nell'attacco della memoria");
            srand(time(NULL));
            //printf("%d\n",getpid());
            fflush(stdout);
            for(int j=0;j<M;j++){
                sleep(rand()%10);
                struct sembuf sem_op;
                sem_op.sem_flg=0;
                sem_op.sem_num=0;
                sem_op.sem_op=-1;
                if(semop(semid,&sem_op,1)==-1) dd_error("errore nell'accesso alla memoria");
                *messaggio = getpid();
                sem_op.sem_flg=0;
                sem_op.sem_num=0;
                sem_op.sem_op=1;
                if(semop(semid,&sem_op,1)==-1) dd_error("errore nell'uscita alla memoria");
            }
            exit(EXIT_SUCCESS);
        }
    }
    for(int i=0;i<M;i++){//processo padre
        sleep(5);
        printf("%d\n",*messaggio);
    }
    while(wait(NULL)!=-1);//aspetto la fine del figlio
    if(semctl(semid,0,IPC_RMID)==-1) dd_error("errore nella deallocazione del semaforo");
    if(shmctl(shmid,IPC_RMID,NULL)==-1) dd_error("errore nella disallocazione della memoria");
}

