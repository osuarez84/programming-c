#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

/*
 * Lesson 2 Milestone Project: Complete Memory Allocator
 * 
 * This file combines all the exercises into a complete memory allocator
 * with first-fit allocation strategy.
 */

// Block header structure
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
    // Allocate memory pool using mmap
    memory_pool = mmap(
        NULL,
        POOL_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0
    );
    
    if (memory_pool == MAP_FAILED) {
        perror("mmap failed");
        return false;
    }
    
    // Set up the initial free block
    free_list = (block_header_t*)memory_pool;
    free_list->size = POOL_SIZE;
    free_list->is_free = true;
    free_list->next = NULL;
    
    return true;
}

// Function to get the usable memory from a block
void* get_usable_memory(block_header_t* block) {
    return (void*)((char*)block + sizeof(block_header_t));
}

// Function to get the block header from usable memory
block_header_t* get_block_header(void* ptr) {
    return (block_header_t*)((char*)ptr - sizeof(block_header_t));
}

// TODO: Implement mem_alloc function
void* mem_alloc(size_t size) {
    // Your implementation here...
    
    // 1. If size is 0, return NULL or a minimal allocation
    // 2. Adjust size for alignment and add header size
    // 3. Search free list for first block that's big enough (first-fit)
    // 4. Split the block if it's much larger than needed
    // 5. Mark the block as allocated and remove from free list
    // 6. Return pointer to usable memory
    
    return NULL;
}

// TODO: Implement mem_free function
void mem_free(void* ptr) {
    // Your implementation here...
    
    // 1. If ptr is NULL, do nothing
    // 2. Get the block header from the pointer
    // 3. Verify the pointer is within our memory pool
    // 4. Mark the block as free
    // 5. Add the block to the free list
    // 6. Optional: Coalesce with adjacent free blocks
}

// Function to print the state of the memory pool
void mem_dump() {
    printf("Memory Pool State\n");
    printf("================\n");
    printf("Pool address: %p\n", memory_pool);
    printf("Pool size: %zu bytes\n", (size_t)POOL_SIZE);
    
    // Scan the entire memory pool for blocks
    block_header_t* current = (block_header_t*)memory_pool;
    int block_count = 0;
    size_t total_allocated = 0;
    size_t total_free = 0;
    
    printf("\nAll blocks:\n");
    while ((void*)current < (void*)((char*)memory_pool + POOL_SIZE)) {
        printf("Block %d: address=%p, size=%zu, is_free=%s\n",
               block_count++,
               (void*)current,
               current->size,
               current->is_free ? "true" : "false");
        
        if (current->is_free) {
            total_free += current->size;
        } else {
            total_allocated += current->size;
        }
        
        // Move to the next block
        current = (block_header_t*)((char*)current + current->size);
    }
    
    printf("\nFree list:\n");
    current = free_list;
    block_count = 0;
    
    while (current != NULL) {
        printf("Free block %d: address=%p, size=%zu\n",
               block_count++,
               (void*)current,
               current->size);
        current = current->next;
    }
    
    printf("\nMemory usage summary:\n");
    printf("Total allocated: %zu bytes\n", total_allocated);
    printf("Total free: %zu bytes\n", total_free);
    printf("Total: %zu bytes\n", total_allocated + total_free);
    
    printf("\n");
}

// Test function
void test_allocator() {
    printf("Testing Memory Allocator\n");
    printf("=======================\n\n");
    
    // Allocate some memory blocks
    printf("Allocating blocks...\n");
    void* ptr1 = mem_alloc(100);
    void* ptr2 = mem_alloc(200);
    void* ptr3 = mem_alloc(300);
    
    printf("Allocated 100 bytes at %p\n", ptr1);
    printf("Allocated 200 bytes at %p\n", ptr2);
    printf("Allocated 300 bytes at %p\n", ptr3);
    
    // Write to the memory to verify it's usable
    if (ptr1) memset(ptr1, 'A', 100);
    if (ptr2) memset(ptr2, 'B', 200);
    if (ptr3) memset(ptr3, 'C', 300);
    
    mem_dump();
    
    // Free the blocks in a different order
    printf("\nFreeing blocks...\n");
    
    printf("Freeing block at %p\n", ptr2);
    mem_free(ptr2);
    mem_dump();
    
    printf("Freeing block at %p\n", ptr1);
    mem_free(ptr1);
    mem_dump();
    
    printf("Freeing block at %p\n", ptr3);
    mem_free(ptr3);
    mem_dump();
    
    // Allocate again to test reuse
    printf("\nAllocating again to test reuse...\n");
    ptr1 = mem_alloc(50);
    ptr2 = mem_alloc(75);
    ptr3 = mem_alloc(100);
    
    printf("Allocated 50 bytes at %p\n", ptr1);
    printf("Allocated 75 bytes at %p\n", ptr2);
    printf("Allocated 100 bytes at %p\n", ptr3);
    
    mem_dump();
    
    // Clean up
    mem_free(ptr1);
    mem_free(ptr2);
    mem_free(ptr3);
}

int main() {
    if (!init_memory_pool()) {
        printf("Failed to initialize memory pool!\n");
        return 1;
    }
    
    printf("Memory pool initialized successfully!\n\n");
    mem_dump();
    
    test_allocator();
    
    printf("\nMemory allocator test completed!\n");
    
    return 0;
}
