#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<sys/wait.h>

static void handler(int sig){
    siginfo_t info;
    if (waitid(P_ALL, -1, &info, WEXITED | WSTOPPED | WCONTINUED) == -1) {
        perror("waitid");
        exit(EXIT_FAILURE);
    }
    switch (info.si_code) {
        case CLD_EXITED:
            printf("Child exited with status %d\n", info.si_status);
            break;
        case CLD_KILLED:
            printf("Child killed by signal %d\n", info.si_status);
            break;
        case CLD_DUMPED:
            printf("Child dumped core, signal %d\n", info.si_status);
            break;
        case CLD_TRAPPED:
            printf("Child trapped\n");
            break;
        case CLD_STOPPED:
            printf("Child stopped by signal %d\n", info.si_status);
            break;
        case CLD_CONTINUED:
            printf("Child continued\n");
            break;
        default:
            printf("Unknown status\n");
            break;
    }
}

int main(){
    pid_t id=fork();
    if(id==-1) exit(1);
    if(id!=0){
        fprintf(stdout,"sono il padre,il mio pid:%d,il pid di mio figlio:%d\n",getpid(),id);
        struct sigaction sa;
        sa.sa_handler=handler;
        sigset_t my_mask;
        sigemptyset(&my_mask);
        sa.sa_mask=my_mask;
        //sa.sa_flags=SA_NODEFER;
        if(sigaction(SIGCHLD,&sa,NULL)==-1) printf("errore nel sigaction\n");
        wait(NULL);
    }else{
        write(STDOUT_FILENO, "ciao\n", 5);
        while(true){
            sleep(1);
        }
        exit(EXIT_FAILURE);
    }
    return 0;
}