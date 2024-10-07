#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include "reverse_to_upper.h"

void swap(char* first,char* second){
    char temp=*first;
    *first=*second;
    *second=temp;
}
/**
 * @brief Receives a string as input, reverses the string, and converts it to uppercase.
 * 
 * @param newString 
 */
void reverse_to_upper(char* newString){
    int j=strlen(newString)-1;
    for(int i=0;i<strlen(newString)/2+1;i++){
        newString[i]=toupper(newString[i]);
        newString[j]=toupper(newString[j]);
        swap(&newString[i],&newString[j]);
        j--;
    }
}

void test_reverse_to_upper() {
    char test1[] = "hello";
    reverse_to_upper(test1);
    printf("Test 1 - Expected: OLLEH, Got: %s\n", test1);

    char test2[] = "world";
    reverse_to_upper(test2);
    printf("Test 2 - Expected: DLROW, Got: %s\n", test2);

    char test3[] = "aBcDe";
    reverse_to_upper(test3);
    printf("Test 3 - Expected: EDCBA, Got: %s\n", test3);

    char test4[] = "12345";
    reverse_to_upper(test4);
    printf("Test 4 - Expected: 54321, Got: %s\n", test4);

    char test5[] = "a1b2c3";
    reverse_to_upper(test5);
    printf("Test 5 - Expected: 3C2B1A, Got: %s\n", test5);

    char test6[] = "";
    reverse_to_upper(test6);
    printf("Test 6 - Expected: , Got: %s\n", test6);
}
