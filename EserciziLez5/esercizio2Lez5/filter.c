#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int c;
    while((c=getchar())!=EOF){
        c=toupper(c);
        if(putchar(c)==EOF){
            perror(NULL);
            exit(EXIT_FAILURE);
        }
        if(c=='\n'){
            fflush(stdout);
        }
    }
    return 0;
}