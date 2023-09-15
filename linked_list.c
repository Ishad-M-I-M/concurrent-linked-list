#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.c"

const int MAX_KEY = 65536;

int iterations = 1000; // number of samples need to provide 95% confidence level
int n = 1000;    // number of elements initially in linked list
int m = 10000;    // number of random operations count

float m_member = 0.99;    // fraction of member operations from m
float m_insert = 0.005;    // fraction of insert operations from m
float m_delete = 0.005;    // fraction of delete operations from m

int operation;
double start_time, finish_time, time_elapsed;

int main(void) {
    double *time_arr = (double *) malloc(iterations * sizeof(double));
    for (int j = 0; j < iterations; j++) {
        struct node *head = NULL;
        int i = 0;
        while (i < n) {
            int r = rand() % MAX_KEY;
            if (insert(r, &head)) {
                i++;
            }
        }

        int member_count = m * m_member;
        int insert_count = m * m_insert;
        int delete_count = m * m_delete;

        start_time = clock();
        for (i = 0; i < m; i++) {
            operation = rand() % 3; // random number 0, 1, 2
            int r = rand() % MAX_KEY;
            if (operation == 0 && member_count > 0) {
                member(r, head);
                member_count--;
            } else if (operation == 1 && insert_count > 0) {
                insert(r, &head);
                insert_count--;
            } else if (operation == 2 && delete_count > 0) {
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

