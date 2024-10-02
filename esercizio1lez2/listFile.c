#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listFile.h"

void test_leggi_lista(){
    //primo test case
    FILE *fp = fopen("lista_nomi.txt", "w");
    fprintf(fp,"%s\n","mario");
    fprintf(fp,"%s\n","luca");
    fprintf(fp,"%s\n","matteo");
    fclose(fp);
    fp=fopen("lista_nomi.txt","r");
    int size=0;
    char** listToControl=leggi_lista(fp,&size);
    stampa_lista(listToControl,size);
    if(size!=3){
        printf("dimensione sbagliata\n");
    } 
    if(strcmp(listToControl[0],"mario")!=0) {
        printf("la riga 0 non è uguale.\n");
        exit(0);
    }else if(strcmp(listToControl[1],"luca")!=0){
        printf("la riga 1 non è uguale.1\n");
        exit(0);
    }else if(strcmp(listToControl[2],"matteo")!=0){
        printf("la riga 2 non è uguale.\n");
        exit(0);
    }else{
        printf("TEST CASE 1 SUPERATO\n");
    }
    fclose(fp);
    // secondo test case: file vuoto
    fp = fopen("lista_nomi_vuota.txt", "w");
    fclose(fp);
    fp=fopen("lista_nomi_vuota.txt","r");
    size = 0;
    listToControl = leggi_lista(fp, &size);
    stampa_lista(listToControl,size);
    if (size != 0) {
        printf("dimensione sbagliata per file vuoto\n");
    } else {
        printf("TEST CASE 2 SUPERATO\n");
    }
    fclose(fp);
    // terzo test case: un solo nome
    fp = fopen("lista_nomi_uno.txt", "w");
    fprintf(fp, "%s\n", "giovanni");
    fclose(fp);
    fp=fopen("lista_nomi_uno.txt","r");
    size = 0;
    listToControl = leggi_lista(fp, &size);
    stampa_lista(listToControl,size);
    if (size != 1) {
        printf("dimensione sbagliata per un solo nome\n");
    } else if (strcmp(listToControl[0], "giovanni") != 0) {
        printf("la riga 0 non è uguale.\n");
        exit(0);
    } else {
        printf("TEST CASE 3 SUPERATO\n");
    }
    fclose(fp);
    // quarto test case: nomi con spazi
    fp = fopen("lista_nomi_spazi.txt", "w");
    fprintf(fp, "%s\n", "anna maria");
    fprintf(fp, "%s\n", "giuseppe");
    fclose(fp);
    fp=fopen("lista_nomi_spazi.txt","r");
    size = 0;
    listToControl = leggi_lista(fp, &size);
    stampa_lista(listToControl,size);
    if (size != 2) {
        printf("dimensione sbagliata per nomi con spazi\n");
    } else if (strcmp(listToControl[0], "anna maria") != 0) {
        printf("la riga 0 non è uguale.\n");
        exit(0);
    } else if (strcmp(listToControl[1], "giuseppe") != 0) {
        printf("la riga 1 non è uguale.4\n");
        exit(0);
    } else {
        printf("TEST CASE 4 SUPERATO\n");
    }
    fclose(fp);
    // quinto test case: nomi duplicati
    fp = fopen("lista_nomi_duplicati.txt", "w");
    fprintf(fp, "%s\n", "paolo");
    fprintf(fp, "%s\n", "paolo");
    fclose(fp);
    fp=fopen("lista_nomi_duplicati.txt","r");
    size = 0;
    listToControl = leggi_lista(fp, &size);
    stampa_lista(listToControl,size);
    if (size != 2) {
        printf("dimensione sbagliata per nomi duplicati\n");
    } else if (strcmp(listToControl[0], "paolo") != 0) {
        printf("la riga 0 non è uguale.\n");
        exit(0);
    } else if (strcmp(listToControl[1], "paolo") != 0) {
        printf("la riga 1 non è uguale.5\n");
        exit(0);
    } else {
        printf("TEST CASE 5 SUPERATO\n");
    }
    fclose(fp);
    // sesto test case: nomi con caratteri speciali
    fp = fopen("lista_nomi_speciali.txt", "w");
    fprintf(fp, "%s\n", "aless@ndro");
    fprintf(fp, "%s\n", "fr@ncesca");
    fclose(fp);
    fp=fopen("lista_nomi_speciali.txt","r");
    size = 0;
    listToControl = leggi_lista(fp, &size);
    stampa_lista(listToControl,size);
    if (size != 2) {
        printf("dimensione sbagliata per nomi con caratteri speciali\n");
    } else if (strcmp(listToControl[0], "aless@ndro") != 0) {
        printf("la riga 0 non è uguale.\n");
        exit(0);
    } else if (strcmp(listToControl[1], "fr@ncesca") != 0) {
        printf("la riga 1 non è uguale.6\n");
        exit(0);
    } else {
        printf("TEST CASE 6 SUPERATO\n");
    }
    fclose(fp);
}
/**
 * @brief restituisce un array di stringhe contenente tutti i nomi del file_in
 * 
 * @param file_in 
 * @param nof_elements 
 * @return char** 
 */
char** leggi_lista(FILE* file_in, int* nof_elements) {
    if(file_in==NULL) return NULL;
    char** arrayString=NULL;
    int size=0;
    char buffer[100];
    while(fgets(buffer,100,file_in)!=NULL){
        char* newline=malloc(strlen(buffer)*sizeof(char)+1);
        if(newline) {
            strcpy(newline,buffer);
            newline[strlen(newline)-1]='\0';
            char** temp=realloc(arrayString, (size + 1) * sizeof(char*));
            if(temp){
                arrayString=temp;
                arrayString[size]=newline;
                size++;
            } else {
                free(newline);
                break;
            }
        }
    }
    *nof_elements=size;
    return arrayString;
}


//
void stampa_lista(char** mio_ar, int n_elems) {
    if(!mio_ar) return;
    for(int i=0;i<n_elems;i++){
        printf("%s\n",mio_ar[i]);
    }
}