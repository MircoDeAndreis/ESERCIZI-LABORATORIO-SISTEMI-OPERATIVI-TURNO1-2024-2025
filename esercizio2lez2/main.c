#include <stdio.h>
#include "name_surname.h"

int main(){
    char* full_name=get_name_And_Surname();
    printf("Full name:%s\nParse name:%s\n",full_name,parse_nome(full_name));
}