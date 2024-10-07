#include <stdio.h>
#include "formatpr.h"

/**
 * @brief Prints a formatted multiplication table.
 *
 * Prints a 10x10 multiplication table with each value in a fixed-width column of 6 characters.
 */
void format_print() {
    for(int i=1;i<=10;i++){
        for(int j=1;j<=10;j++) printf("%6d",i*j);
        printf("\n");
    }
}