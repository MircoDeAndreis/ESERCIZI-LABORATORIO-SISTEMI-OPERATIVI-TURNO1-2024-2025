#include<stdio.h>
#include<string.h>
#include <assert.h>
#include "cifrario_di_Cesare.h"

/**
 * @brief This function decrypts the given string using a Caesar cipher with a shift of 2.
 * 
 * @param string 
 */
void decoder(char* string){
    int size=strlen(string);
    for(int i=0;i<size;i++){
        string[i]-=2;
        if(string[i]!=' '+2 && string[i]!='\n'+2 && string[i]!='\t'+2 && (string[i]<'a' || (string[i]<'A' && string[i]>'z'))) string[i]+='z'-'a'+1; 
    }
}



void test_decoder() {
    char test1[] = "cde";
    decoder(test1);
    assert(strcmp(test1, "abc") == 0);

    char test2[] = "efg";
    decoder(test2);
    assert(strcmp(test2, "cde") == 0);

    char test3[] = "yz";
    decoder(test3);
    assert(strcmp(test3, "wx") == 0);

    char test4[] = "ab";
    decoder(test4);
    assert(strcmp(test4, "yz") == 0);

    char test5[] = "";
    decoder(test5);
    assert(strcmp(test5, "") == 0);
}