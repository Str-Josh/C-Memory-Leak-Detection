#include "MemoryLeakDetector.h"


struct Node* linkedListHead = NULL;
struct heapUsageStruct heapUsage;

void* malloc_leakDetect(size_t size) {
    void* allocatedStorage = malloc(size);
    if (linkedListHead == NULL) {
        linkedListHead = createNewNode(allocatedStorage, size, __FILE__, __LINE__);
        heapUsage.allocs = 1;
        heapUsage.deallocs = 0;
        heapUsage.totalBytesAlloc = size;
        heapUsage.totalBytesFreed = 0;
    }
    else {
        insertBack(linkedListHead, allocatedStorage, size, __FILE__, __LINE__);
        heapUsage.allocs += 1;
        heapUsage.totalBytesAlloc += size;
    }
    return allocatedStorage;
}

void* calloc_leakDetect(size_t num, size_t size) { return NULL; }

void* realloc_leakDetect(void* ptr, size_t new_size) { return NULL; }

void free_leakDetect(void* allocatedMemory) {
    if (linkedListHead == NULL) { printf("Linked List is empty.\n"); return; }
    if (allocatedMemory == NULL) {
        printf("There was no memory allocated at the given address.\n");
        return;
    }
    struct Node* allocatedMemoryNode = search(linkedListHead, allocatedMemory);
    if (allocatedMemoryNode != NULL) {
        deleteAt(&linkedListHead, (void*)allocatedMemoryNode);
        heapUsage.totalBytesFreed += allocatedMemoryNode->allocatedMemorySize;
    }
    heapUsage.deallocs += 1;
    free(allocatedMemory);
}

void displayLeakDetectionReport() {
    // displayContents(linkedListHead);
    int totalMemoryLeaks = heapUsage.allocs - heapUsage.deallocs;
    int totalMemoryLeakSize = heapUsage.totalBytesAlloc - heapUsage.totalBytesFreed;
    printf("Total memory leaks found:  %d\n================================\n", totalMemoryLeaks);
    
    // Convert bytes to largest possible units.
    double totalMemoryLeakSize_converted = (double)totalMemoryLeakSize;
    const char* possibleSizeInterpretations[3] = { "MB", "KB", "Bytes" };
    const char* sizeInterpretation;
    if (totalMemoryLeakSize > 1000000) {
        // megabytes
        totalMemoryLeakSize_converted *= 0.000001;
        sizeInterpretation = possibleSizeInterpretations[0];
    }
    else if (totalMemoryLeakSize > 1000) {
        // kilobytes
        totalMemoryLeakSize_converted *= 0.001;
        sizeInterpretation = possibleSizeInterpretations[1];
    }
    else {
        /* Don't convert to anything different. */
        sizeInterpretation = possibleSizeInterpretations[2];
    }
    if (sizeInterpretation == NULL) {  // I have no clue when this would actually be hit but just in case.
        printf("Apparently sizeInterpretation is null for some reason.\n");
        return;
    }
    printf("Total memory leaked:  %f %s\n", totalMemoryLeakSize_converted, sizeInterpretation);

    // printf("\n\n\n");
    // displayContents(linkedListHead);
}