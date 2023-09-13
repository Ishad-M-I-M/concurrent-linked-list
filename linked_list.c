#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.c"

struct node {
    int val;
    struct node *next;
};

int member(int value, struct node *head);

int insert(int value, struct node **head);

int delete(int value, struct node **head);

void clearMemory(struct node **head);

int iterations = 385; // number of samples need to provide 95% confidence level
int n = 1000;    // number of elements initially in linked list
int m = 10000;    // number of random operations count

float m_member = 0.50;    // fraction of member operations from m
float m_insert = 0.25;    // fraction of insert operations from m
float m_delete = 0.25;    // fraction of delete operations from m

float operation;
double start_time, finish_time, time_elapsed;

int main(void) {
    double *time_arr = (double *) malloc(iterations * sizeof(double));
    for (int j = 0; j < iterations; j++) {
        struct node *head = NULL;
        int i = 0;
        while (i < n) {
            int r = rand() % 65536;
            if (insert(r, &head)) {
                i++;
            }
        }

        int member_count = m * m_member;
        int insert_count = m * m_insert;
        int delete_count = m * m_delete;

        start_time = clock();
        for (i = 0; i < m; i++) {
            operation = (rand() % m) / m; // random number between 0 and m
            int r = rand() % 65536;
            if (operation < m_member && member_count > 0) {
                member(r, head);
                member_count--;
            } else if (m_member < operation < m_member + m_insert && insert_count > 0) {
                insert(r, &head);
                insert_count--;
            } else if (m_member + m_insert < operation < m_member + m_insert + m_delete && delete_count > 0) {
                delete(r, &head);
                delete_count--;
            } else {
                i--;
            }
        }
        finish_time = clock();
        time_elapsed = (finish_time - start_time) / CLOCKS_PER_SEC;
        printf("Time elapsed\t %i: %f\n", j, time_elapsed);

        time_arr[j] = time_elapsed;
        clearMemory(&head);
    }

    double avg = average(time_arr, iterations);
    double std = standardDeviation(time_arr, iterations);
    printf("Average : %f\nStandard Deviation: %f\n", avg, std);

    return 0;
}


int member(int value, struct node *head) {
    struct node *current;

    current = head;
    while (current != NULL && current->val < value)
        current = current->next;

    if (current == NULL || current->val > value) {
        return 0;
    } else {
        return 1;
    }
}

int insert(int value, struct node **headp) {
    struct node *current = *headp;
    struct node *previous = NULL;
    struct node *temp;

    while (current != NULL && current->val < value) {
        previous = current;
        current = current->next;
    }

    if (current == NULL || current->val > value) {
        temp = malloc(sizeof(struct node));
        temp->val = value;
        temp->next = current;
        if (previous == NULL) {
            *headp = temp;
        } else {
            previous->next = temp;
        }
        return 1;
    } else {
        return 0;
    }
}

int delete(int value, struct node **headp) {
    struct node *current = *headp;
    struct node *previous = NULL;

    while (current != NULL && current->val < value) {
        previous = current;
        current = current->next;
    }

    if (current != NULL && current->val == value) {
        if (previous == NULL) {
            *headp = current->next;
            free(current);
        } else {
            previous->next = current->next;
            free(current);
        }
        return 1;
    } else {
        return 0;
    }
}


void clearMemory(struct node **headp) {
    struct node *current;
    struct node *next;

    current = *headp;
    next = current->next;
    while (next != NULL) {
        free(current);
        current = next;
        next = current->next;
    }
    free(current);
    *headp = NULL;
}

