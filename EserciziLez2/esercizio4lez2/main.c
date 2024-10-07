#include "reverse_to_upper.h"
#include<stdio.h>

int main() {
    printf("Inserire una frase:");
    char buffer[256];
    fgets(buffer,256,stdin);
    printf("String that you entered: %s", buffer);
    reverse_to_upper(buffer);
    printf("Result: %s\n", buffer);
    return 0;
}