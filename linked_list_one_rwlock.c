#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "utils.c"

const int MAX_KEY = 65536;

struct node {
    int data;
    struct node *next;
};

struct thread_data {
    int i; // thread number
    int member_count;   // number of member operations in thread
    int insert_count;   // number of insert operations in thread
    int delete_count;   // number of delete operations in thread
};

struct node *head;
 
const int iterations = 1000; // number of samples need to provide 95% confidence level
const int n = 1000;         // number of elements initially in linked list
const int m = 10000;   // number of random operations count

const float m_member = 0.99;    // fraction of member operations from m
const float m_insert = 0.005;    // fraction of insert operations from m
const float m_delete = 0.005;   // fraction of delete operations from m

int thread_count = 1;    // number of threads

double start_time, finish_time, time_elapsed;

int member_count, insert_count, delete_count;

pthread_rwlock_t rwlock;

int member(int value);

int insert(int value);

int delete(int value);

void clearMemory(void);

void *threadFunction(void *rank);

int main() {
    double *time_arr = (double *) malloc(iterations * sizeof(double));
    for (int j = 0; j < iterations; j++) {
        head = NULL;
        member_count = m_member * m;
        insert_count = m_insert * m;
        delete_count = m_delete * m;

        int i = 0;
        while (i < n) {
            int r = rand() % 65536;
            if (insert(r)) {
                i++;
            }
        }

        pthread_t *thread_handles;

        thread_handles = malloc(thread_count * sizeof(pthread_t));
        pthread_rwlock_init(&rwlock, NULL);

        start_time = clock();
        
        struct thread_data **data_arr = malloc(thread_count * sizeof(struct thread_data *));
        for (i = 0; i < thread_count; i++){
            struct thread_data* data = malloc(sizeof(struct thread_data));
            data->i = i;
            if (i == thread_count -1){
                data->member_count = member_count;
                data->insert_count = insert_count;
                data->delete_count = delete_count;
            } else {
                member_count -= member_count/thread_count;
                data->member_count = member_count/thread_count;
                insert_count -= insert_count/thread_count;
                data->insert_count = insert_count/thread_count;
                delete_count -= delete_count/thread_count;
                data->delete_count = delete_count/thread_count;
            }
            data_arr[i] = data;
            pthread_create(&thread_handles[i], NULL, threadFunction, (void *) data_arr[i]);
        }

        for (i = 0; i < thread_count; i++)
            pthread_join(thread_handles[i], NULL);

        finish_time = clock();
        time_elapsed = (finish_time - start_time) / CLOCKS_PER_SEC;
        printf("Time elapsed\t %i: %f\n", j, time_elapsed);

        time_arr[j] = time_elapsed;

        clearMemory();
        pthread_rwlock_destroy(&rwlock);
        free(thread_handles);
    }
    double avg = average(time_arr, iterations);
    double std = standardDeviation(time_arr, iterations);
    printf("Average : %f\nStandard Deviation: %f\n", avg, std);

    free(time_arr);
    return 0;
}

//member Function
int member(int value) {
    struct node *temp;

    temp = head;
    while (temp != NULL && temp->data < value)
        temp = temp->next;

    if (temp == NULL || temp->data > value) {
        //printf("%d is a member in linked-list\n", value);
        return 0;
    } else {
        //printf("%d is a member in linked-list\n", val
        return 1;
    }
}

// insert function
int insert(int value) {
    struct node *current = head;
    struct node *pred = NULL;
    struct node *temp;
    int return_value = 1;

    while (current != NULL && current->data < value) {
        pred = current;
        current = current->next;
    }

    if (current == NULL || current->data > value) {
        temp = malloc(sizeof(struct node));
        temp->data = value;
        temp->next = current;
        if (pred == NULL)
            head = temp;
        else
            pred->next = temp;
    } else {
        return_value = 0;
    }
    return return_value;
}

//delete Function
int delete(int value) {
    struct node *current = head;
    struct node *pred = NULL;
    int return_value = 1;

    while (current != NULL && current->data < value) {
        pred = current;
        current = current->next;
    }

    if (current != NULL && current->data == value) {
        if (pred == NULL) {
            head = current->next;
            free(current);
        } else {
            pred->next = current->next;
            free(current);
        }
    } else {
        return_value = 0;
        //printf("%d is not in the linked-list\n", value);
    }

    return return_value;
}

//Function to free memory used for linked-list
void clearMemory(void) {
    struct node *currentent;
    struct node *next;

    currentent = head;
    next = currentent->next;
    while (next != NULL) {
        free(currentent);
        currentent = next;
        next = currentent->next;
    }
    free(currentent);
}


void *threadFunction(void *data) {
    int i, val;

    struct thread_data* my_data = data;
    int my_member = my_data->member_count;
    int my_insert = my_data->insert_count;
    int my_delete = my_data->delete_count;

    int ops_per_thread = m / thread_count;

    for (i = 0; i < my_member + my_insert + my_delete; i++) {
        float operation = rand()%3;
        val = rand() % MAX_KEY;

        if (operation == 0 && my_member > 0) {
            pthread_rwlock_rdlock(&rwlock);
            member(val);
            pthread_rwlock_unlock(&rwlock);
            my_member--;
        } else if (operation == 1 && my_insert > 0) {
            pthread_rwlock_wrlock(&rwlock);
            insert(val);
            pthread_rwlock_unlock(&rwlock);
            my_insert--;
        } else if (operation == 2 && my_delete > 0) {
            pthread_rwlock_wrlock(&rwlock);
            delete(val);
            pthread_rwlock_unlock(&rwlock);
            my_delete--;
        } else {
            i--;
        }
    }
    return NULL;
}
