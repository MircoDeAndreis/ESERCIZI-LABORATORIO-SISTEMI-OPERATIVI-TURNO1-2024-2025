#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>


void errExit(char* msg) {
	fprintf(stdout, "error with message: *%s*\nexiting...\n", msg);
	exit(EXIT_FAILURE);	
}


 
int main(void) {
    int     c;

    while ((c = getchar()) != EOF) {
        if (isupper(c))
          c = tolower(c);
				if(islower(c))
					c = toupper(c);
        if (putchar(c) == EOF)
          errExit("output error");
        if (c == '\n')
           fflush(stdout);
    }
    exit(0);
}