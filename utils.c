#include <math.h>

struct node {
    int val;
    struct node *next;
};

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

double average(const double arr[], int length) {
    if (length <= 0) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 0; i < length; i++) {
        sum += arr[i];
    }

    return sum / length;
}

double standardDeviation(const double arr[], int length) {
    if (length <= 1) {
        return 0.0;
    }

    double mean = average(arr, length);
    double sumSquaredDiff = 0.0;

    for (int i = 0; i < length; i++) {
        double diff = arr[i] - mean;
        sumSquaredDiff += diff * diff;
    }

    double variance = sumSquaredDiff / (length - 1);
    return sqrt(variance);
}