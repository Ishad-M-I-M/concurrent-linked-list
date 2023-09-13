#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "utils.c"

const int MAX_KEY = 65536;

struct node {
    int val;
    struct node *next;
};

struct node *head;

int iterations = 385; // number of samples need to provide 95% confidence level
int n = 1000;    // number of elements initially in linked list
int m = 10000;    // number of random operations count

float m_member = 0.99;    // fraction of member operations from m
float m_insert = 0.005;    // fraction of insert operations from m
float m_delete = 0.005;    // fraction of delete operations from m

int thread_count = 2;    // number of threads

double start_time, finish_time, time_elapsed;

int member_count;
int insert_count;
int delete_count;

pthread_mutex_t mutex;
pthread_mutex_t count_mutex;

int member(int value);

int insert(int value);

int delete(int value);

void clearMemory(void);

void *threadFunction(void *rank);

int main() {
    double *time_arr = (double *) malloc(iterations * sizeof(double));
    for (int j = 0; j < iterations; j++) {
        head = NULL;
        member_count = 0;
        insert_count = 0;
        delete_count = 0;

        int i = 0;
        while (i < n) {
            int r = rand() % 65536;
            if (insert(r)) {
                i++;
            }
        }

        pthread_t *thread_handles;

        thread_handles = malloc(thread_count * sizeof(pthread_t));
        pthread_mutex_init(&mutex, NULL);
        pthread_mutex_init(&count_mutex, NULL);

        start_time = clock();
        for (i = 0; i < thread_count; i++)
            pthread_create(&thread_handles[i], NULL, threadFunction, (void *) i);

        for (i = 0; i < thread_count; i++)
            pthread_join(thread_handles[i], NULL);

        finish_time = clock();
        time_elapsed = (finish_time - start_time) / CLOCKS_PER_SEC;
        printf("Time elapsed\t %i: %f\n", j, time_elapsed);

        time_arr[j] = time_elapsed;

        clearMemory();
        pthread_mutex_destroy(&mutex);
        pthread_mutex_destroy(&count_mutex);
        free(thread_handles);
    }

    double avg = average(time_arr, iterations);
    double std = standardDeviation(time_arr, iterations);
    printf("Average : %f\nStandard Deviation: %f\n", avg, std);

    free(time_arr);
    return 0;
}

int member(int value) {
    struct node *temp;

    temp = head;
    while (temp != NULL && temp->val < value)
        temp = temp->next;

    if (temp == NULL || temp->val > value) {
        return 0;
    } else {
        return 1;
    }
}

int insert(int value) {
    struct node *current = head;
    struct node *previous = NULL;
    struct node *temp;
    int return_value = 1;

    while (current != NULL && current->val < value) {
        previous = current;
        current = current->next;
    }

    if (current == NULL || current->val > value) {
        temp = malloc(sizeof(struct node));
        temp->val = value;
        temp->next = current;
        if (previous == NULL)
            head = temp;
        else
            previous->next = temp;
    } else {
        return_value = 0;
    }

    return return_value;
}

int delete(int value) {
    struct node *current = head;
    struct node *previous = NULL;
    int return_value = 1;

    while (current != NULL && current->val < value) {
        previous = current;
        current = current->next;
    }

    if (current != NULL && current->val == value) {
        if (previous == NULL) {
            head = current->next;
            free(current);
        } else {
            previous->next = current->next;
            free(current);
        }
    } else {
        return_value = 0;
    }
    return return_value;
}

void clearMemory(void) {
    struct node *current;
    struct node *next;

    current = head;
    next = current->next;
    while (next != NULL) {
        free(current);
        current = next;
        next = current->next;
    }
    free(current);
}

void *threadFunction(void *rank) {
    int i, val;

    int my_member = 0;
    int my_insert = 0;
    int my_delete = 0;

    int ops_per_thread = m / thread_count;

    for (i = 0; i < ops_per_thread; i++) {
        float operation_choice = (rand() % 10000 / 10000);
        val = rand() % MAX_KEY;

        if (operation_choice < m_member) {
            pthread_mutex_lock(&mutex);
            member(val);
            pthread_mutex_unlock(&mutex);
            my_member++;
        } else if (operation_choice < m_member + m_insert) {
            pthread_mutex_lock(&mutex);
            insert(val);
            pthread_mutex_unlock(&mutex);
            my_insert++;
        } else {
            pthread_mutex_lock(&mutex);
            delete(val);
            pthread_mutex_unlock(&mutex);
            my_delete++;
        }
    }

    pthread_mutex_lock(&count_mutex);
    member_count += my_member;
    insert_count += my_insert;
    delete_count += my_delete;
    pthread_mutex_unlock(&count_mutex);
    return NULL;
}

