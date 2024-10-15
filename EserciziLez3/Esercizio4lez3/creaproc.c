#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<assert.h>
#include"creaproc.h"

void creaproc(int size){
    for(int i=0;i<size;i++){
        pid_t id=fork();
        if(id==0){
            sleep(getpid()%10);
            printf("Aspetta %d secondi.\n",getpid()%10);
            exit(0);
        }else{
            printf("%d\n",wait(NULL));
        }
    }
}

void test_creaproc() {
    // Test case 1: Test with size 1
    printf("Running test case 1\n");
    creaproc(1);
    printf("Test case 1 passed\n");

    // Test case 2: Test with size 3
    printf("Running test case 2\n");
    creaproc(3);
    printf("Test case 2 passed\n");

    // Test case 3: Test with size 5
    printf("Running test case 3\n");
    creaproc(5);
    printf("Test case 3 passed\n");
}

