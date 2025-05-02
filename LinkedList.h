#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void* __real_malloc(size_t size);
void* __real_calloc(size_t num, size_t size);
void* __real_realloc(void* ptr, size_t new_size);
void  __real_free(void* ptr);

struct Node {
    struct Node* next;

    void* memoryAddress;
    size_t allocatedMemorySize;
    char* fileName;
    int lineLocation;
};

struct Node* createNewNode(void* memoryAddress, size_t allocatedMemorySize, const char* filename, int lineLocation);

void insertFront(struct Node* head, void* memoryAddress, size_t allocatedMemorySize, const char* filename, int lineLocation);

void insertBack(struct Node* head, void* memoryAddress, size_t allocatedMemorySize, const char* filename, int lineLocation);

void deleteFront(struct Node* head);

void deleteBack(struct Node* head, int position);

void deleteAt(struct Node** head, void* memoryAddressComparer);

int count(struct Node* head);

void displayContents(struct Node* head);

void reverseOrder(struct Node* head);

struct Node* search(struct Node* head, void* memoryAddress);

#endif