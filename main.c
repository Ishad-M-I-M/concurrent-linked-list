
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "LinkedList.h"

unsigned int* getUniqueRandomNumbers(unsigned int n);
void serialLikedListOperations();
void linkedListWithMutexOperations();
void linkedListWithReadWriteLockOperations();

unsigned int max_value = 65535; // 2^16-1
unsigned int* used; // To keep track of used numbers

int main(int argc, char *argv[]){
    if (argc != 7){
        printf("Provide required arguments\n");
        return EXIT_FAILURE;
    }
    used = (unsigned int*)calloc(max_value, sizeof(unsigned int));
    if (used == NULL) {
        printf("Memory allocation failed");
        return EXIT_FAILURE;
    }

    unsigned int option = atoi(argv[1]);
    unsigned int n = atoi(argv[2]);
    unsigned int m = atoi(argv[3]);
    double m_member = atof(argv[4]);
    double m_insert = atof(argv[5]);
    double m_delete = atof(argv[6]);

    if (m_member+ m_insert + m_delete != 1){
        printf("Fractions not sum up to 1");
        return EXIT_FAILURE;
    }

    unsigned int* numbers = getUniqueRandomNumbers(n);

    switch (option) {
        case 1:
            struct Node* head = populateLinkedList(n, numbers);
            struct Node* current = head;
            while (current->next != NULL){
                printf("%i\n", current->data);
                current = current->next;
            }
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            printf("Provided option is invalid");
    }

    free(numbers);
    return EXIT_SUCCESS;
}

unsigned int* getUniqueRandomNumbers(unsigned int n) {
    // Seed the random number generator with the current time
    srand(time(NULL));

    unsigned int* randomNumbers = (unsigned int*)malloc(n * sizeof(unsigned int));
    if (randomNumbers == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    unsigned int i = 0;
    while (i < n) {
        unsigned int randomNum;
        do {
            randomNum = rand() % (max_value + 1);
        } while (used[randomNum] != 0);

        randomNumbers[i] = randomNum;
        i++;
    }

    return randomNumbers;
}

void serialLikedListOperations(){

}