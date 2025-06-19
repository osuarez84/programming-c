#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/mman.h>

/*
 * Exercise 1: Design a Block Header Structure
 * 
 * In this exercise, you'll design a block header structure that will be used
 * by your memory allocator to keep track of memory blocks.
 */

// TODO: Define your block header structure here
// Consider what information you need to track for each memory block
typedef struct block_header {
    // Hint: You'll need to track at least:
    // - The size of the block
    // - Whether the block is free or in use
    // - A way to link blocks together (for a free list)
    
    // Your implementation here...
    size_t size;
    bool is_free;
    struct block_header* next;
    
} block_header_t;

// Function to initialize a block header
void init_block_header(block_header_t* header, size_t size, bool is_free) {
    // TODO: Initialize the header fields
    // Your implementation here...
    block_header_t* block = (block_header_t*)header;
    block->size = size;
    block->is_free = is_free;
    block->next = NULL;
}

// Function to print block header information
void print_block_header(block_header_t* header) {
    // TODO: Print the header fields
    // Your implementation here...
    printf("Block Header at %p:\n", (void*)header);
    // Print other fields...
    printf("Size: %zu\n", header->size);
    printf("Is it free?: %s\n", header->is_free ? "FREE" : "ALLOCATED");
    printf("Next free block at address %p\n", header->next);
}

// This function demonstrates how the block header would be used
// in a memory allocator
void demonstrate_block_header_usage() {
    printf("Block Header Structure Demo\n");
    printf("==========================\n\n");
    
    // TODO: Create and initialize a sample block header
    // Your implementation here...
    size_t size = 4096;
    block_header_t* mem_block = mmap(
        NULL,
        size,
        PROT_READ | PROT_WRITE,
        MAP_ANONYMOUS | MAP_PRIVATE,
        -1,
        0
    );
    if (mem_block == MAP_FAILED) {
        perror("mmap failed");
    }

    init_block_header(mem_block, size, true);

    // TODO: Print the block header information
    // Your implementation here...
    print_block_header(mem_block);
    

    printf("\nThis is how your memory allocator will use block headers:\n");
    printf("1. When allocating memory, it will search for a free block\n");
    printf("2. When it finds a suitable block, it will mark it as 'in use'\n");
    printf("3. When freeing memory, it will find the header and mark it as 'free'\n");
    printf("4. Headers allow the allocator to keep track of all memory blocks\n");

    munmap(mem_block, size);
}

int main() {
    demonstrate_block_header_usage();
    return 0;
}
