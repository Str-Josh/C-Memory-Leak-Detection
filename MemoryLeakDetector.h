#ifndef MEMORY_LEAK_DETECTOR_H
#define MEMORY_LEAK_DETECTOR_H

#include "LinkedList.h"


void* __real_malloc(size_t size);
void* __real_calloc(size_t num, size_t size);
void* __real_realloc(void* ptr, size_t new_size);
void  __real_free(void* ptr);

struct heapUsageStruct {
    int allocs;
    int deallocs;
    size_t totalBytesAlloc;
    size_t totalBytesFreed;
};

void* __wrap_malloc(size_t size);

void* __wrap_calloc(size_t num, size_t size);

void* __wrap_realloc(void* ptr, size_t new_size);

void __wrap_free(void* allocatedMemory);

static void displayLeakDetectionReport();

#endif