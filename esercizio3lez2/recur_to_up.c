#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include "recur_to_up.h"


void test_recur_to_up() {
    char test1[] = "hello";
    recur_to_up(test1);
    printf("Test 1: %s\n", strcmp(test1, "HELLO") == 0 ? "Passed" : "Failed");

    char test2[] = "WORLD";
    recur_to_up(test2);
    printf("Test 2: %s\n", strcmp(test2, "WORLD") == 0 ? "Passed" : "Failed");

    char test3[] = "123abc";
    recur_to_up(test3);
    printf("Test 3: %s\n", strcmp(test3, "123ABC") == 0 ? "Passed" : "Failed");

    char test4[] = "";
    recur_to_up(test4);
    printf("Test 4: %s\n", strcmp(test4, "") == 0 ? "Passed" : "Failed");

    char test5[] = "MiXeD CaSe";
    recur_to_up(test5);
    printf("Test 5: %s\n", strcmp(test5, "MIXED CASE") == 0 ? "Passed" : "Failed");
}

/**
 * @brief Receives a string as input and transforms it to uppercase.
 * 
 * @param in_str 
 */
void recur_to_up(char* in_str){
    if(in_str==NULL || *in_str=='\0' || *in_str=='\n') return;
    *in_str=toupper(*in_str);
    in_str++;
    recur_to_up(in_str);
}