#include<stdio.h>
#include "recur_to_up.h"

int main(){
    printf("Inserire una stringa da convertire:");
    char buffer[256];
    fgets(buffer, 256, stdin);
    recur_to_up(buffer);
    printf("%s\n",buffer);
}