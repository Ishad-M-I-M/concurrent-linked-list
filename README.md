# Linked List Implementations

Implementations of a linked list as a:
a) Serial program
b) Parallel program (based on Pthreads) with one mutex for the entire linked list
c) Parallel program (based on Pthreads) with read-write locks for the entire linked list

How to compile and run the programs:
* linked_list.c
```shell
gcc -o linked_list linked_list.c
./linked_list
```

According to the case the following can be changed:
```c
int n = 1000;    // number of elements initially in linked list
int m = 10000;    // number of random operations count

float m_member = 0.50;    // fraction of member operations from m
float m_insert = 0.25;    // fraction of insert operations from m
float m_delete = 0.25;    // fraction of delete operations from m
```

