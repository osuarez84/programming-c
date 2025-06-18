# Lesson 2: Basic Memory Allocator

## Introduction

In Lesson 1, you learned about memory fundamentals and how to request memory directly from the operating system using `sbrk()` and `mmap()`. Now, we'll build on that knowledge to create a simple memory allocator that implements the first-fit allocation strategy.

This lesson focuses on designing a memory allocator that can:
1. Allocate memory blocks of requested sizes
2. Free previously allocated blocks
3. Keep track of which blocks are in use and which are free
4. Reuse freed memory when possible

## Key Concepts

### Memory Block Headers

Every memory allocator needs to track metadata about each allocated block. This typically includes:

- **Size**: How large the block is
- **Status**: Whether the block is free or in use
- **Adjacent blocks**: Pointers to neighboring blocks (for coalescing later)

### Free and Allocated Block Tracking

There are several ways to track free blocks:
- **Free list**: A linked list of free blocks
- **Bitmaps**: Using bits to represent block status
- **Boundary tags**: Metadata at both ends of blocks

For our implementation, we'll use a linked list approach.

### First-Fit Allocation Strategy

The first-fit strategy is simple:
1. Start at the beginning of the free list
2. Walk through the list until you find a block large enough
3. Use that block (potentially splitting it if it's much larger than needed)

While not the most efficient strategy, it's straightforward to implement and understand.

## Exercises

### Exercise 1: Design a Block Header Structure

Create a header structure that contains:
- Block size
- Status flag (free/allocated)
- Pointers for a linked list

### Exercise 2: Implement Basic Memory Pool

Create a memory pool using `mmap()` and set up the initial free block.

### Exercise 3: Implement mem_alloc()

Implement a function that:
1. Takes a size parameter
2. Searches the free list for a suitable block (first-fit)
3. Marks the block as allocated
4. Returns a pointer to the usable memory

### Exercise 4: Implement mem_free()

Implement a function that:
1. Takes a pointer to previously allocated memory
2. Finds the corresponding block header
3. Marks the block as free
4. Adds it to the free list

### Exercise 5: Write Tests

Create test cases to verify that your allocator:
- Can allocate memory of different sizes
- Can free memory
- Can reuse freed memory
- Handles edge cases properly

## Milestone Project

Combine all the exercises into a complete memory allocator that provides:
- `void* mem_alloc(size_t size)`: Allocates memory
- `void mem_free(void* ptr)`: Frees memory
- `void mem_dump()`: Prints the current state of the memory pool

## Resources

- [Doug Lea's Memory Allocator Paper](http://gee.cs.oswego.edu/dl/html/malloc.html)
- [Inside malloc](https://sourceware.org/glibc/wiki/MallocInternals)
- [Memory Management in C](https://www.cs.cmu.edu/~fp/courses/15213-s07/lectures/17-allocation.pdf)
