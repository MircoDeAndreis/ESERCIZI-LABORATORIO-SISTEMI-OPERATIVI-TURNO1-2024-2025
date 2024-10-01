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

    int size=0;
    char** listToControl=leggi_lista(fp,&size);
    if(size!=3){
        printf("dimensione sbagliata\n");
    } 
    if(strcmp(listToControl[0],"mario")!=0) {
        printf("la riga 0 non è uguale.\n");
        exit(0);
    }else if(strcmp(listToControl[1],"luca")!=0){
        printf("la riga 1 non è uguale.\n");
        exit(0);
    }else if(strcmp(listToControl[2],"matteo")!=0){
        printf("la riga 2 non è uguale.\n");
        exit(0);
    }else{
        printf("TEST CASE 1 SUPERATO\n");
    }
    // secondo test case: file vuoto
    fp = fopen("lista_nomi_vuota.txt", "w");
    fclose(fp);

    size = 0;
    listToControl = leggi_lista(fp, &size);
    if (size != 0) {
        printf("dimensione sbagliata per file vuoto\n");
    } else {
        printf("TEST CASE 2 SUPERATO\n");
    }

    // terzo test case: un solo nome
    fp = fopen("lista_nomi_uno.txt", "w");
    fprintf(fp, "%s\n", "giovanni");
    fclose(fp);

    size = 0;
    listToControl = leggi_lista(fp, &size);
    if (size != 1) {
        printf("dimensione sbagliata per un solo nome\n");
    } else if (strcmp(listToControl[0], "giovanni") != 0) {
        printf("la riga 0 non è uguale.\n");
        exit(0);
    } else {
        printf("TEST CASE 3 SUPERATO\n");
    }

    // quarto test case: nomi con spazi
    fp = fopen("lista_nomi_spazi.txt", "w");
    fprintf(fp, "%s\n", "anna maria");
    fprintf(fp, "%s\n", "giuseppe");
    fclose(fp);

    size = 0;
    listToControl = leggi_lista(fp, &size);
    if (size != 2) {
        printf("dimensione sbagliata per nomi con spazi\n");
    } else if (strcmp(listToControl[0], "anna maria") != 0) {
        printf("la riga 0 non è uguale.\n");
        exit(0);
    } else if (strcmp(listToControl[1], "giuseppe") != 0) {
        printf("la riga 1 non è uguale.\n");
        exit(0);
    } else {
        printf("TEST CASE 4 SUPERATO\n");
    }

    // quinto test case: nomi duplicati
    fp = fopen("lista_nomi_duplicati.txt", "w");
    fprintf(fp, "%s\n", "paolo");
    fprintf(fp, "%s\n", "paolo");
    fclose(fp);

    size = 0;
    listToControl = leggi_lista(fp, &size);
    if (size != 2) {
        printf("dimensione sbagliata per nomi duplicati\n");
    } else if (strcmp(listToControl[0], "paolo") != 0) {
        printf("la riga 0 non è uguale.\n");
        exit(0);
    } else if (strcmp(listToControl[1], "paolo") != 0) {
        printf("la riga 1 non è uguale.\n");
        exit(0);
    } else {
        printf("TEST CASE 5 SUPERATO\n");
    }

    // sesto test case: nomi con caratteri speciali
    fp = fopen("lista_nomi_speciali.txt", "w");
    fprintf(fp, "%s\n", "aless@ndro");
    fprintf(fp, "%s\n", "fr@ncesca");
    fclose(fp);

    size = 0;
    listToControl = leggi_lista(fp, &size);
    if (size != 2) {
        printf("dimensione sbagliata per nomi con caratteri speciali\n");
    } else if (strcmp(listToControl[0], "aless@ndro") != 0) {
        printf("la riga 0 non è uguale.\n");
        exit(0);
    } else if (strcmp(listToControl[1], "fr@ncesca") != 0) {
        printf("la riga 1 non è uguale.\n");
        exit(0);
    } else {
        printf("TEST CASE 6 SUPERATO\n");
    }
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
    while(feof(file_in) == 0 ){
        char* newLine=malloc(51*sizeof(char));
        fgets(newLine,51,file_in);
        size++;
        char** temp=realloc(arrayString,size);
        if(temp==NULL) break;
        arrayString=temp;
        arrayString[size-1]=newLine;
    }
    *nof_elements=size;
    return arrayString;
}
//
void stampa_lista(char** mio_ar, int n_elems) {
}