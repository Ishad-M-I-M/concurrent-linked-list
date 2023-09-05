# Linked List Implementations

Executing the program
* To build the project executable run 
```shell
cmake
```
and then run
```shell
make
```
> This will generate an executable named `concurrent-linked-list`.
* To run the program
```shell
./concurrent-linked-list <option>
```
> Accepted option values:
> * `1` - Serial program.
> * `2` - Parallel program (based on Pthreads) with one mutex for the entire linked list.
> * `3` - Parallel program (based on Pthreads) with read-write locks for the entire linked list.
