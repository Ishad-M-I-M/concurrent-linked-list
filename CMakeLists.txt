cmake_minimum_required(VERSION 3.0)
project(concurrent_linked_list C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(concurrent_linked_list
        main.c
        LinkedListWithMutex.c
        LinkedListWithMutex.h
        SerialLinkedList.c
        SerialLinkedList.h
        LinkedListWithReadWriteLocks.c
        LinkedListWithReadWriteLocks.h)
