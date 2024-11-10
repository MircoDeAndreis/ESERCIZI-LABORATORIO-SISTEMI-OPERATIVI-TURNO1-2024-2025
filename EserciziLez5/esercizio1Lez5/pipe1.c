#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#define BUF_SIZE 256


int main(int argc, char *argv[]) {
    int pfd[2]; /* pipe file descriptors */
    char buf[BUF_SIZE];
    ssize_t numRead;
    if ((argc != 2 && argc!=3) || strcmp(argv[1], "--help") == 0){
        printf("./pipe1 stringa da inserire\n"); /* stampa formato invocazione */
        exit(EXIT_SUCCESS);
    }    
    if (pipe(pfd) == -1){ /* creo il pipe */
        perror("Pipe non aperta\n"); /* gestione errore */
        exit(EXIT_FAILURE);
    }
    switch (fork()) {
        case -1:
           perror("fork non avvenuta\n");
           exit(EXIT_FAILURE);
        case 0: /* ------ figlio - legge dal pipe -------- */
            if (close(pfd[1]) == -1){ /* chiusura write end */
                perror("chiusura pipe fallita\n"); /* gestione errore */
                exit(EXIT_FAILURE);
            }
            for (;;) { /* legge dal pipe, e scrive su stdout */
                numRead = read(pfd[0], buf, BUF_SIZE);
                if (numRead == -1){
                    perror("lettura fallita"); /* gestione errore */
                    exit(EXIT_FAILURE);
                }
                if (numRead == 0)
                    break; /* End-of-file */
                if (write(STDOUT_FILENO, buf, numRead) != numRead){
                    perror("scrittura fallita"); /* gestione errore */
                    exit(EXIT_FAILURE);
                }
            }
            write(STDOUT_FILENO, "\n", 1);
            if (close(pfd[0]) == -1){
                perror("chiusura pipe in scrittura fallita"); /* gestione errore */
                exit(EXIT_FAILURE);
            }
            if(argc==3){
                int pfd1[2];
                if (pipe(pfd1) == -1){ /* creo il pipe */
                    perror("Pipe non aperta\n"); /* gestione errore */
                    exit(EXIT_FAILURE);
                }
                switch(fork()){
                    case -1:
                        perror("errore nella fork");
                        exit(EXIT_FAILURE);
                    case 0://processo figlio
                        if(close(pfd1[1])==-1){
                            perror("chiusura pipe fallita\n"); /* gestione errore */
                            exit(EXIT_FAILURE);
                        }
                        for (;;) { /* legge dal pipe, e scrive su stdout */
                            numRead = read(pfd1[0], buf, BUF_SIZE);
                            if (numRead == -1){
                                perror("lettura fallita"); /* gestione errore */
                                exit(EXIT_FAILURE);
                            }
                            if (numRead == 0)
                                break; /* End-of-file */
                            if (write(STDOUT_FILENO, buf, numRead) != numRead){
                                perror("scrittura fallita"); /* gestione errore */
                                exit(EXIT_FAILURE);
                            }
                        }
                        if (write(STDOUT_FILENO, "\n", 1) != 1){
                            perror("scrittura fallita"); /* gestione errore */
                            exit(EXIT_FAILURE);
                        }
                        if(close(pfd1[0])==-1){
                            perror("chiusura pipe fallita\n"); /* gestione errore */
                            exit(EXIT_FAILURE);
                        }
                        exit(EXIT_SUCCESS);
                    default:
                        if(close(pfd1[0])==-1){
                            perror("chiusura pipe fallita\n"); /* gestione errore */
                            exit(EXIT_FAILURE);
                        }
                        if(write(pfd1[1],argv[2],strlen(argv[2]))!=strlen(argv[2])){
                            perror("scrittura fallita");
                            exit(EXIT_FAILURE);
                        }
                        if(write(pfd1[1],"\n",1)!=1){
                            perror("scrittura fallita");
                            exit(EXIT_FAILURE);
                        }
                        if(close(pfd1[1])==-1){
                            perror("chiusura pipe fallita\n"); /* gestione errore */
                            exit(EXIT_FAILURE);
                        }
                        exit(EXIT_SUCCESS);
                }
            }
            exit(EXIT_SUCCESS);
        default: /* ------ padre - scrive sul pipe -------- */
            if (close(pfd[0]) == -1){ /* chiusura del read end */
                perror("chiusura canale lettura"); /* gestione errore */
                exit(EXIT_FAILURE);
            }
            if(write(pfd[1],argv[1],strlen(argv[1]))!=strlen(argv[1])){
                perror("scrittura nel pipe fallita"); /* gestione errore */
                exit(EXIT_FAILURE);
            }
            if (close(pfd[1]) == -1){ /* il figlio riceverà EOF */
                perror("chiusura canale scrittura fallita"); /* gestione errore */
                exit(EXIT_FAILURE);
            } 
            wait(NULL); /* attesa della terminazione del figlio */
            exit(EXIT_SUCCESS);
    } // end switch
}