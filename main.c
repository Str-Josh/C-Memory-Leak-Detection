#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MemoryLeakDetector.h"


int main() {
    int* exampleIntArray = (int*)malloc_leakDetect(5*sizeof(int));  // Allocating memory
    
    // Note: Freeing the allocated memory using the below wrapper for 'free', result will show no memory leaks.
    // free_leakDetect(exampleIntArray);

    printf("\n\n");
    displayLeakDetectionReport();
    printf("\n\n");

    /* Note: 
    *  Uncommenting the following will add another memory leak.
    *  You'll see the addition in the displayLeakDetectionreport().
    */

    // int* someStorage = (int*)malloc_leakDetect(5*sizeof(int));
    // someStorage[0] = 2;
    // someStorage[2] = 3;
    // someStorage[4] = 1;

    // displayLeakDetectionReport();

    printf("Program executed successfully.");
    return 1;
}