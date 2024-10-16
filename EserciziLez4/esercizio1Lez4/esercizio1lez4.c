#include<stdio.h>
#include<signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(){
    pid_t id=fork();
    if(id==-1){
        fprintf(stderr,"Processo figlio non creato");
        exit(EXIT_FAILURE);
    }else if(id==0){
        printf("Sono il processo figlio.\n");
        while(true){
            sleep(10);
        }
    }else{
        kill(id,SIGTERM);
        int status;
        waitpid(id, &status, 0);
        if (WIFSIGNALED(status)) {
            printf("Il processo figlio è terminato a causa del segnale: %s\n", strsignal(WTERMSIG(status)));
        } else {
            printf("Il processo figlio non è terminato a causa di un segnale.\n");
        }
    }
}