#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main(){
    FILE* pipe;
    if((pipe=popen("./filter","r"))==NULL){
        perror("pipe non creata");
        exit(EXIT_FAILURE);
    }
    ssize_t numlett;
    char buffer[256];
    while(1){
        fputs("prompt>",stdout);
        fflush(stdout);
        if(fgets(buffer,256,pipe)==NULL) break;
        if(fputs(buffer,stdout)==EOF) exit(EXIT_FAILURE);
    }
    pclose(pipe);
    return 0;
}