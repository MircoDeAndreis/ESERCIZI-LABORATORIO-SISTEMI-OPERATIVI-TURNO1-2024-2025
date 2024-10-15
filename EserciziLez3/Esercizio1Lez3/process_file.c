#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"process_file.h"

void test_manage_file(){
    //TEST CASE 1:
    FILE* fp=fopen("prova.txt","w+");
    if(fp==NULL) return;
    char* test1[]={"Pippo","Mario","Nello","Luigi"};
    printf("NOMI INSERITI:\nPippo\nMario\nNello\nLuigi\n");
    printf("NOMI STAMPATI:\n");
    manage_file(fp,test1,4);
    fclose(fp);

    //TEST CASE 2: Empty array
    fp=fopen("prova2.txt","w+");
    if(fp==NULL) return;
    char* test2[] = {};
    printf("NOMI INSERITI:\n");
    printf("NOMI STAMPATI:\n");
    manage_file(fp,test2,0);
    fclose(fp);

    //TEST CASE 3: NULL file pointer
    char* test3[] = {"Anna", "Elsa"};
    printf("NOMI INSERITI:\nAnna\nElsa\n");
    printf("NOMI STAMPATI:\n");
    manage_file(NULL, test3, 2);

    //TEST CASE 4: NULL names array
    fp=fopen("prova4.txt","w+");
    if(fp==NULL) return;
    printf("NOMI INSERITI:\n");
    printf("NOMI STAMPATI:\n");
    manage_file(fp, NULL, 2);
    fclose(fp);

    //TEST CASE 5: Large number of names
    fp=fopen("prova5.txt","w+");
    if(fp==NULL) return;
    char* test5[100];
    for(int i=0; i<100; i++){
        test5[i] = "TestName";
    }
    printf("NOMI INSERITI:\nTestName (x100)\n");
    printf("NOMI STAMPATI:\n");
    manage_file(fp, test5, 100);
    fclose(fp);
}
/**
 * @brief Receives an array of strings as input, writes them to a file, and then prints all the names that were written to the file.
 * 
 * @param fp 
 * @param nomi 
 * @param size 
 */
void manage_file(FILE* fp,char** nomi,int size){
    if(nomi==NULL || fp==NULL) return;
    pid_t id=fork();
    if(id==-1){
        exit(1);
    }else if(id==0){
        for(int i=0;i<size;i++){
            fputs(nomi[i],fp);
            fprintf(fp,"\n");
            //printf("Processo figlio\n");
        }
        exit(0);
    }else{
        wait(NULL);
        char buffer[256];
        int dim=0;
        rewind(fp);
        while(fgets(buffer,256,fp)){
            printf("%s",buffer);
            //printf("Processo padre");
        }
    }
}