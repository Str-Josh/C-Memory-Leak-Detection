#include "MemoryLeakDetector.h"


#include <stdlib.h>
#include <stdio.h>

void* __real_malloc(size_t size);
void* __real_calloc(size_t num, size_t size);
void* __real_realloc(void* ptr, size_t new_size);
void  __real_free(void* ptr);

struct Node* linkedListHead = NULL;
struct heapUsageStruct heapUsage;

void* __wrap_malloc(size_t size) {
    void* allocatedStorage = __real_malloc(size);
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

void* __wrap_calloc(size_t num, size_t size) { return NULL; }

void* __wrap_realloc(void* ptr, size_t new_size) {
    if (ptr == NULL) { return __wrap_malloc(new_size); }
    if (new_size == 0) { __wrap_free(ptr); return NULL; }
    return NULL;
}

void __wrap_free(void* allocatedMemory) {
    if (allocatedMemory == NULL) {
        printf("There was no memory allocated at the given address.\n");
        return;
    }
    if (linkedListHead == NULL) { printf("Linked List is empty.\n"); return; }
    
    struct Node* allocatedMemoryNode = search(linkedListHead, allocatedMemory);
    if (allocatedMemoryNode) {
        deleteAt(&linkedListHead, (void*)allocatedMemoryNode);
        heapUsage.totalBytesFreed += allocatedMemoryNode->allocatedMemorySize;
    }

    heapUsage.deallocs += 1;
    __real_free(allocatedMemory);
}

__attribute__((destructor))
static void displayLeakDetectionReport() {
    int totalMemoryLeaks = heapUsage.allocs - heapUsage.deallocs;
    int totalMemoryLeakSize = heapUsage.totalBytesAlloc - heapUsage.totalBytesFreed;
    if (!totalMemoryLeaks) {
        printf("There weren't any memory leaks detected!");
        return;
    }
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
    if (sizeInterpretation == NULL) {
        printf("Apparently sizeInterpretation is null for some reason.\n");
        return;
    }
    printf("Total memory leaked:  %f %s\n", totalMemoryLeakSize_converted, sizeInterpretation);
}