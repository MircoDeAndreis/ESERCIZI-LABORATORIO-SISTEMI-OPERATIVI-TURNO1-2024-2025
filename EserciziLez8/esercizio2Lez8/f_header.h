#define SHKEY 0x1234
#define SEMKEY 0x1235
#define MAX_TRIES 10

#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>

#define WRITE 0
#define READ 1

void dd_error(char* error){
    perror(error);
    exit(1);
}

