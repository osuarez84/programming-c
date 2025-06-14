# Memory Allocator Learning Project

## Introduction

This project guides you through building your own memory allocator from scratch. By the end of this series of lessons, you'll understand how memory allocation works under the hood, the trade-offs involved in different allocation strategies, and have implemented your own allocator that can replace standard functions like `malloc()`, `free()`, `calloc()`, and `realloc()`.

## Prerequisites

- Solid understanding of C programming
- Familiarity with pointers and memory concepts
- Basic knowledge of data structures (linked lists, trees)
- Understanding of computer architecture fundamentals

## Learning Roadmap

### Lesson 1: Memory Fundamentals
**Goal:** Understand how memory works at the system level

**Topics:**
- Virtual memory vs physical memory
- Process memory layout (stack, heap, data, text)
- System calls for memory management (`brk`, `sbrk`, `mmap`)

**Exercises:**
1. Write a program that prints the addresses of variables in different segments
2. Experiment with `sbrk()` to request memory directly from the OS
3. Use `mmap()` to allocate a chunk of memory and write to it

**Milestone:** Create a simple function that requests a block of memory from the OS

### Lesson 2: Basic Memory Allocator
**Goal:** Implement a naive first-fit allocator

**Topics:**
- Memory block headers and metadata
- Free and allocated block tracking
- First-fit allocation strategy

**Exercises:**
1. Design a block header structure
2. Implement `mem_alloc()` using first-fit strategy
3. Implement `mem_free()` (without coalescing)
4. Write tests to verify basic allocation/deallocation

**Milestone:** Working allocator that can allocate and free memory (with fragmentation issues)

### Lesson 3: Improving the Allocator
**Goal:** Address fragmentation and improve efficiency

**Topics:**
- External vs internal fragmentation
- Free block coalescing
- Split blocks to reduce waste

**Exercises:**
1. Modify `mem_free()` to coalesce adjacent free blocks
2. Implement block splitting in `mem_alloc()`
3. Add debugging functions to visualize heap state
4. Benchmark your allocator against simple allocation patterns

**Milestone:** Allocator with reduced fragmentation and better space efficiency

### Lesson 4: Advanced Allocation Strategies
**Goal:** Implement and compare different allocation algorithms

**Topics:**
- Best-fit allocation
- Worst-fit allocation
- Next-fit allocation
- Segregated free lists

**Exercises:**
1. Implement best-fit allocation strategy
2. Implement segregated free lists for common sizes
3. Create benchmarks to compare different strategies
4. Analyze trade-offs between strategies

**Milestone:** Multiple allocation strategies with performance comparison data

### Lesson 5: Full-Featured Allocator
**Goal:** Complete the allocator with all standard functions

**Topics:**
- Implementing `calloc()` and `realloc()`
- Thread safety considerations
- Error handling and edge cases

**Exercises:**
1. Implement `mem_calloc()`
2. Implement `mem_realloc()`
3. Add proper error handling
4. Make allocator thread-safe (optional advanced challenge)

**Milestone:** Complete memory allocator that can be used as a drop-in replacement for standard functions

### Lesson 6: Advanced Topics
**Goal:** Explore specialized allocation techniques

**Topics:**
- Buddy system allocator
- Slab allocation
- Pool allocators
- Garbage collection basics

**Exercises:**
1. Implement a simple buddy system allocator
2. Create a pool allocator for fixed-size objects
3. Experiment with a simple mark-and-sweep garbage collector

**Milestone:** Specialized allocators for different use cases

## Final Project

Build a complete memory allocator library that:
1. Provides drop-in replacements for standard memory functions
2. Offers multiple allocation strategies that can be selected at runtime
3. Includes debugging features (leak detection, usage statistics)
4. Is well-documented and tested
5. Demonstrates measurable performance characteristics

## Recommended Resources

1. **Books:**
   - "The C Programming Language" by Kernighan and Ritchie
   - "Operating Systems: Three Easy Pieces" (Memory Management chapters)

2. **Online Resources:**
   - [Doug Lea's Memory Allocator Paper](http://gee.cs.oswego.edu/dl/html/malloc.html)
   - [jemalloc Documentation](http://jemalloc.net/jemalloc.3.html)
   - [glibc malloc Implementation](https://sourceware.org/glibc/wiki/MallocInternals)

3. **Reference Implementations:**
   - dlmalloc (Doug Lea's allocator)
   - jemalloc (Facebook's allocator)
   - tcmalloc (Google's allocator)

## Project Structure

```
mem_alloc/
├── src/                # Source code
│   ├── mem_alloc.c    # Main implementation
│   └── mem_alloc.h    # Header file
├── tests/              # Test cases
├── benchmarks/         # Performance tests
└── examples/           # Example usage
```

Happy allocating!
