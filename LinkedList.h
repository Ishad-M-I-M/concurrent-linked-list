
#include <stdbool.h>

#ifndef CONCURRENT_LINKED_LIST_SERIALLINKEDLIST_H
#define CONCURRENT_LINKED_LIST_SERIALLINKEDLIST_H
struct Node {
    int data;
    struct Node* next;
};

struct Node *populateLinkedList(unsigned int n, unsigned int* numbers);
void insert(struct Node **head, int value);
void delete(struct Node **head, int value);
bool member(struct Node **head, int value);
#endif //CONCURRENT_LINKED_LIST_SERIALLINKEDLIST_H
