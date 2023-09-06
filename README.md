# Linked List Implementations

Executing the program
* To build the project executable run 
```shell
cmake .
```
and then run
```shell
make
```
> This will generate an executable named `concurrent-linked-list`.
* To run the program
```shell
./concurrent-linked-list <option> <n> <m> <m_member> <m_insert> <m_delete>
```
> - `option` - To specify the linked list type to be used. Accepted values:
>   * `1` - Serial program.
>   * `2` - Parallel program (based on Pthreads) with one mutex for the entire linked list.
>   * `3` - Parallel program (based on Pthreads) with read-write locks for the entire linked list.
> 
> - `n` - Number of elements to be in initially populated linked list.
> - `m` - Number of random operations to be carried out.
> - `m_member` - Fraction of member operations in `m` random operations.
> - `m_insert` - Fraction of insert operations in `m` random operations.
> - `m_delete` - Fraction of delete operations in `m` random operations.
