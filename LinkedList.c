
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "LinkedList.h"

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

struct Node *populateLinkedList(unsigned int n, unsigned int* numbers){
    struct Node* head = NULL;
    for (int i =0; i < n; i++){
        insert(&head, numbers[i]);
    }
    return head;
}

void insert(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void delete(struct Node** head, int value) {
    if (*head == NULL) {
        return;
    }

    if ((*head)->data == value) {
        struct Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    struct Node* current = *head;
    while (current->next != NULL) {
        if (current->next->data == value) {
            struct Node* temp = current->next;
            current->next = temp->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}

bool member(struct Node **head, int value){
    struct Node* current = *head;
    while (current != NULL) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}