#include<stdio.h>
#include<signal.h>
#include<errno.h>

int main(){
    pid_t id;
    printf("inserire un processo che si vuole analizzare:");
    fscanf(stdin, "%d", &id);
    if(kill(id,0)==-1){
        if(errno==ESRCH){
            perror("PROCESS DOESN'T EXIST");
        }else if(errno==EPERM){
            perror("PROCESS EXISTS BUT WE DON'T HAVE PERMISSION TO ACCESS IT");
        }
    }else{
        printf("The process %d exists and can receive signals from this process.", (int)id);
    }
}