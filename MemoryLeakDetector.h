#ifndef MEMORY_LEAK_DETECTOR_H
#define MEMORY_LEAK_DETECTOR_H

#include <stdlib.h>
#include "LinkedList.h"

struct heapUsageStruct {
    int allocs;
    int deallocs;
    size_t totalBytesAlloc;
    size_t totalBytesFreed;
};

void* malloc_leakDetect(size_t size);

void* calloc_leakDetect(size_t num, size_t size);

void* realloc_leakDetect(void* ptr, size_t new_size);

void free_leakDetect(void* allocatedMemory);

void displayLeakDetectionReport();

#endif