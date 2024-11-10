#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
    int parg[2];
    if (pipe(parg) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    for(int i=1;i<argc;i++){
        if(fork()==0){
            if(close(parg[0])==-1){
                perror("chiusura fallita");
                exit(EXIT_FAILURE);
            }
            sleep(atoi(argv[i]));
            if(close(parg[1])==-1){
                perror("chiusura fallita");
                exit(EXIT_FAILURE);
            }
            printf("tempo impiegato:%d\n",atoi(argv[i]));
            puts("stampa riuscita");
            fflush(stdout);
            exit(EXIT_SUCCESS);
        }
    }
    if(close(parg[1])==-1){
        perror("chiusura fallita");
        exit(EXIT_FAILURE);
    }
    char buffer[1];
    read(parg[0], buffer, 1);
    if(close(parg[0])==-1){
        perror("chiusura fallita");
        exit(EXIT_FAILURE);
    }
    puts("padre terminato");
    fflush(stdout);
    exit(EXIT_SUCCESS);
}
