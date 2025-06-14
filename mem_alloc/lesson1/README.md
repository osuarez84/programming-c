# Lesson 1: Memory Fundamentals

## Introduction

Before we can build a memory allocator, we need to understand how memory works at the system level. This lesson covers the fundamentals of memory management in operating systems and how programs interact with memory.

## Key Concepts

### Virtual Memory vs Physical Memory

**Physical Memory**: The actual RAM hardware in your computer.

**Virtual Memory**: An abstraction provided by the operating system that gives each process the illusion of having its own continuous memory space.

Benefits of virtual memory:
- Processes can use more memory than physically available (using disk as swap)
- Memory isolation between processes
- Memory protection
- Simplified memory model for programmers

### Process Memory Layout

A typical process memory layout includes:

```
High addresses
+------------------+
|      Stack       | <- Grows downward (toward lower addresses)
|        ↓         |    - Function call frames
|                  |    - Local variables
+------------------+
|        ↑         |
|                  |
|    Free space    |
|                  |
|        ↓         |
+------------------+
|       Heap       | <- Grows upward (toward higher addresses)
|        ↑         |    - Dynamically allocated memory
+------------------+
|   Uninitialized  |
|       Data       | <- BSS segment (Block Started by Symbol)
|    (bss seg)     |    - Uninitialized global/static variables
+------------------+
|   Initialized    |
|       Data       | <- Data segment
|   (data seg)     |    - Initialized global/static variables
+------------------+
|       Text       | <- Code segment
|                  |    - Program instructions
+------------------+
Low addresses
```

### System Calls for Memory Management

**brk/sbrk**: Traditional way to extend the heap.
- `void *sbrk(intptr_t increment)`: Increases the program's data space by `increment` bytes
- `int brk(void *addr)`: Sets the end of the data segment to `addr`

**mmap**: Modern way to request memory from the OS.
- `void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)`
- Can be used to map files into memory or to allocate anonymous memory

## Exercises

### Exercise 1: Memory Segment Exploration

Create a program that demonstrates different memory segments by printing the addresses of:
- Local variables (stack)
- Dynamically allocated memory (heap)
- Global variables (data segment)
- Function code (text segment)

### Exercise 2: Using sbrk()

Write a program that:
1. Gets the initial program break
2. Requests memory using sbrk()
3. Writes data to that memory
4. Demonstrates that the memory persists between function calls

### Exercise 3: Using mmap()

Create a program that:
1. Allocates memory using mmap()
2. Writes and reads data from that memory
3. Properly unmaps the memory when done

## Milestone Project

Combine what you've learned to create a simple function called `mem_chunk()` that:
1. Takes a size parameter
2. Uses either sbrk() or mmap() to request memory from the OS
3. Returns a pointer to the allocated memory
4. Keeps track of the allocated memory for future reference

This will be the foundation for our memory allocator in future lessons.

## Resources

- [Linux man pages for sbrk](https://man7.org/linux/man-pages/man2/brk.2.html)
- [Linux man pages for mmap](https://man7.org/linux/man-pages/man2/mmap.2.html)
- [Process Memory Layout in C](https://www.geeksforgeeks.org/memory-layout-of-c-program/)
