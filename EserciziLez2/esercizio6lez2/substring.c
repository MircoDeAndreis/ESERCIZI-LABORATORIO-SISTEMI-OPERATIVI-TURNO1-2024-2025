#include<stdio.h>
#include<string.h>
#include <assert.h>
#include "substring.h"
void test_substring() {
    // Test case 1: File with multiple instances of "computational" in different lines
    FILE *fp1 = tmpfile();
    fputs("computational\ncomputational\ncomputational\n", fp1);
    rewind(fp1);
    assert(substring(fp1) == 3);
    fclose(fp1);

    // Test case 2: File with one instance of "computational" in one line
    FILE *fp2 = tmpfile();
    fputs("This is a computational test.\n", fp2);
    rewind(fp2);
    assert(substring(fp2) == 1);
    fclose(fp2);

    // Test case 3: File with no instances of "computational"
    FILE *fp3 = tmpfile();
    fputs("This is a test.\n", fp3);
    rewind(fp3);
    assert(substring(fp3) == 0);
    fclose(fp3);

    // Test case 4: Empty file
    FILE *fp4 = tmpfile();
    rewind(fp4);
    assert(substring(fp4) == 0);
    fclose(fp4);

    // Test case 5: File with "computational" in different cases
    FILE *fp5 = tmpfile();
    fputs("computational\ncomputatonal\ncomput\n", fp5);
    rewind(fp5);
    assert(substring(fp5) == 1); // Assuming case-sensitive search
    fclose(fp5);
}

/**
 * @brief receive a file, search how many times there are the word computational.
 * 
 * @param fp 
 * @return int 
 */
int substring(FILE* fp){
    if(!fp) return 0;
    char buffer[256];
    int somma=0;
    while(fgets(buffer,256,fp)!=0){
        if(strstr(buffer,"computational")!=NULL) somma++;
    }
    return somma;
}