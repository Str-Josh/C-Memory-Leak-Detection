#include "LinkedList.h"


struct Node* createNewNode(void* memoryAddress, size_t allocatedMemorySize, const char* filename, int lineLocation) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->memoryAddress = memoryAddress;
    newNode->allocatedMemorySize = allocatedMemorySize;
    newNode->fileName = (char*)filename;
    newNode->lineLocation = lineLocation;
    newNode->next = NULL;
    return newNode;
}

void insertFront(struct Node* head, void* memoryAddress, size_t allocatedMemorySize, const char* filename, int lineLocation) {
    struct Node* newNode = createNewNode(memoryAddress, allocatedMemorySize, filename, lineLocation);
    newNode->next = head;
    head = newNode;
}

void insertBack(struct Node* head, void* memoryAddress, size_t allocatedMemorySize, const char* filename, int lineLocation) {
    struct Node* newNode = createNewNode(memoryAddress, allocatedMemorySize, filename, lineLocation);
    if (head == NULL) {
        head = newNode;
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void deleteFront(struct Node* head) {
    if (head == NULL) { printf("The list is empty.\n"); return; }
    struct Node* temp = head;
    head = temp->next;
    free(temp);
}

void deleteBack(struct Node* head, int position) {
    if (head == NULL) { printf("The list is empty.\n"); return; }
    struct Node* temp = head;
    if (temp->next == NULL) {
        free(temp);
        head = NULL;
        return;
    }
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

void deleteAt(struct Node** head, void* memoryAddressComparer) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    while (temp != NULL) {
        if ((void*)temp == memoryAddressComparer) {
            if (prev == NULL) {
                *head = temp->next;
            }
            else {
                prev->next = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    return;
}

void displayContents(struct Node* head) {
    if (head == NULL) { printf("The linked list is empty.\n"); return; }

    if (head->next == NULL) {
        printf("Memory Address   :  %p\n", head->memoryAddress);
        printf("Allocated Size   :  %zu bytes\n", head->allocatedMemorySize);
        // printf("Source File Name :  %s\n", head->fileName);
        // printf("Line Number      :  %d\n", head->lineLocation);
        return;
    }

    while (head != NULL) {
        printf("Memory Address   :  %p\n", head->memoryAddress);
        printf("Allocated Size   :  %zu bytes\n", head->allocatedMemorySize);
        // printf("Source File Name :  %s\n", head->fileName);
        // printf("Line Number      :  %d\n", head->lineLocation);
        printf("\n\n");
        head = head->next;
    }
}

int count(struct Node* head) {
    int count = 0;
    struct Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void reverseOrder(struct Node* head) {  }

struct Node* search(struct Node* head, void* memoryAddress) {
    if (head == NULL) { printf("Linked List is empty.\n"); return NULL; }
    if (head->memoryAddress == memoryAddress) {
        /// printf("First element was found.\n");
        return head;
    }
    if (head->next == NULL) {
        /// printf("next elem was null.\n");
        return NULL;
    }

    while (head->next->next != NULL) {
        if (head->memoryAddress == memoryAddress) {
            return head;
        }
        head = head->next;
    }
    printf("Could not find associated Node with memory address: %p", memoryAddress);
    return NULL;
}
