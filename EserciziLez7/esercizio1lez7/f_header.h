#define keysem 0x123456
#define V 1
#define P -1
#define MAX_TRIES 10
#include <stdio.h>
#include <stdlib.h>

void dd_error(char* error){
    perror(error);
    exit(1);
}