#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXLINE 1024

void errExit(char* msg) {
	fprintf(stdout, "error with message: *%s*\nexiting...\n", msg);
	exit(EXIT_FAILURE);	
}


int main(int argc, char** argv) {
    char    line[MAXLINE];
    FILE    *fpin;

    if ((fpin = popen("./filter_per_pipe", "r")) == NULL)
        errExit("popen error");
    for ( ; ; ) {
        fputs("prompt> ", stdout);
        fflush(stdout);
        if (fgets(line, MAXLINE, fpin) == NULL) // lettura dal pipe
            break;
        if (fputs(line, stdout) == EOF)
            errExit("fputs error to pipe");
    }
    if (pclose(fpin) == -1)
        errExit("pclose error");
    putchar('\n');
    exit(0);
}
