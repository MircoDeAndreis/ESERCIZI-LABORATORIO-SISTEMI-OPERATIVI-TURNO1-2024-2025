#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/**
 * @brief Get the name and surname from standard input
 * 
 * @return char* 
 */
char* get_name_And_Surname(){
    printf("Insert name and surname (separate name and surname with a space or a tab):");
    char* buffer=malloc(sizeof(char)*256);
    fgets(buffer, 256, stdin);
    buffer[strlen(buffer)-1]='\0';
    return buffer;
}
/**
 * @brief Receives an input string containing <name, surname> separated by a space or a tab
 * 
 * @param stringa_completa 
 * @return char* 
 */
char* parse_nome(char* stringa_completa){
    if(!stringa_completa) return NULL;
    int i=0;
    while(stringa_completa[i]!=' ' && stringa_completa[i]!='\t' && stringa_completa[i]!='\0' && stringa_completa[i]!='\n') i++;
    char* ret=malloc(i*sizeof(char)+1);
    strncpy(ret, stringa_completa, i);
    ret[i]='\0';
    return ret;
}

void test_parse_name() {
    char* test_cases[] = {
        "John Doe",
        "Alice Wonderland",
        "Bob\tBuilder",
        "Charlie Brown",
        "Dora\tExplorer",
        ""
    };

    for (int i = 0; i<5; i++) {
        char* full_name = strdup(test_cases[i]);
        char* name = parse_nome(full_name);
        printf("Full Name: %s, Parsed Name: %s\n", test_cases[i], name);
        free(full_name);
    }
}