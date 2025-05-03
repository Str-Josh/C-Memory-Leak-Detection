#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    // int* exampleIntArray = (int*)malloc(5*sizeof(int));  // Allocating memory

    // Note: Freeing the allocated memory will result show no memory leaks.
    // free(exampleIntArray);

    /* Note: 
    *  Uncommenting the following will add another memory leak.
    *  The addition in the after program execution.
    */

    // int* someStorage = (int*)malloc(5*sizeof(int));
    // someStorage[0] = 2;
    // someStorage[2] = 3;
    // someStorage[4] = 1;

    return 1;
}