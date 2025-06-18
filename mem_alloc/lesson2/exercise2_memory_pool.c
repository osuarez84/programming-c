#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <unistd.h>

/*
 * Exercise 2: Implement Basic Memory Pool
 * 
 * In this exercise, you'll create a memory pool using mmap()
 * and set up the initial free block.
 */

// Use the block header structure you designed in Exercise 1
typedef struct block_header {
    size_t size;          // Size of the block (including header)
    bool is_free;         // Whether the block is free
    struct block_header* next; // Next block in the free list
    // You may add more fields if needed
} block_header_t;

// Global variables for the memory pool
#define POOL_SIZE (1024 * 1024)  // 1MB memory pool
static void* memory_pool = NULL;  // Pointer to the memory pool
static block_header_t* free_list = NULL;  // Head of the free list

// Function to initialize the memory pool
bool init_memory_pool() {
    // TODO: Use mmap() to allocate a memory pool of POOL_SIZE bytes
    // Your implementation here...
    
    // TODO: Set up the initial free block that spans the entire pool
    // Your implementation here...
    
    return true;  // Return true if initialization was successful
}

// Function to print the state of the memory pool
void print_memory_pool_state() {
    printf("Memory Pool State\n");
    printf("================\n");
    printf("Pool address: %p\n", memory_pool);
    printf("Pool size: %d bytes\n", POOL_SIZE);
    
    // TODO: Print information about the free list
    // Your implementation here...
    
    printf("\n");
}

int main() {
    printf("Memory Pool Initialization\n");
    printf("=========================\n\n");
    
    if (!init_memory_pool()) {
        printf("Failed to initialize memory pool!\n");
        return 1;
    }
    
    printf("Memory pool initialized successfully!\n\n");
    print_memory_pool_state();
    
    printf("This memory pool will be used by your allocator to satisfy allocation requests.\n");
    printf("When you implement mem_alloc(), it will search this pool for free blocks.\n");
    
    return 0;
}
