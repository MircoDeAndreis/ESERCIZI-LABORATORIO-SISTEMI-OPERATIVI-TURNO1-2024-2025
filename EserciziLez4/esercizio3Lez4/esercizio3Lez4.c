#include<stdio.h>
#include<signal.h>
#include<errno.h>

int main(){
    pid_t id;
    printf("INSERT A PROCESS ID THAT YOU WANT TO ANALYZE:");
    fscanf(stdin, "%d", &id);
    if(kill(id,0)==-1){ 
        if(errno==ESRCH){
            perror("PROCESS DOESN'T EXIST");
        }else if(errno==EPERM){
            perror("PROCESS EXISTS BUT WE DON'T HAVE PERMISSION TO ACCESS IT");
        }
    }else{
        printf("THE PROCESS %d EXISTS AND CAN RECEIVE SIGNALS FROM THIS PROCESS.\n", (int)id);
    }
}