# Linked List Implementations

Implementations of a linked list as a:
a) Serial program - [linked_list.c](linked_list.c)
b) Parallel program (based on Pthreads) with one mutex for the entire linked list - [linked_list_one_mutex.c](linked_list_one_mutex.c)
c) Parallel program (based on Pthreads) with read-write locks for the entire linked list - [linked_list_one_rwlock.c](linked_list_one_rwlock.c)

How to compile and run the programs:
* linked_list.c
```shell
gcc -o linked_list linked_list.c -lm
./linked_list
```

* linked_list_one_mutex.c
```shell
gcc -o linked_list_one_mutex linked_list_one_mutex.c -lm -pthread
./linked_list_one_mutex
```

According to the case the following can be changed:
```c
int n = 1000;    // number of elements initially in linked list
int m = 10000;    // number of random operations count

float m_member = 0.50;    // fraction of member operations from m
float m_insert = 0.25;    // fraction of insert operations from m
float m_delete = 0.25;    // fraction of delete operations from m
```

Additionally in (b) and (c) programs the thread count also need be changed.
```c
int thread_count = 1;	// number of threads
```
