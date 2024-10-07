#include<stdio.h>
#include<string.h>
/**
 * @brief receive a file, search how many times there are the word computational.
 * 
 * @param fp 
 * @return int 
 */
int substring(FILE* fp){
    if(!fp) return 0;
    char buffer[256];
    int somma=0;
    while(fgets(buffer,256,fp)!=0){
        if(strstr(buffer,"computational")!=NULL) somma++;
    }
    return somma;
}