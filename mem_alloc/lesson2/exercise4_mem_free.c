#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <unistd.h>

/*
 * Exercise 4: Implement mem_free()
 * 
 * In this exercise, you'll implement a function that frees previously
 * allocated memory and adds it back to the free list.
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

// A simplified mem_alloc implementation for testing
void* mem_alloc(size_t size) {
    // Ensure minimum size and alignment
    size_t aligned_size = (size + sizeof(block_header_t) + 7) & ~7;
    
    // First-fit search
    block_header_t* current = free_list;
    block_header_t* prev = NULL;
    
    while (current != NULL) {
        if (current->is_free && current->size >= aligned_size) {
            // Found a suitable block
            
            // Split the block if it's much larger than needed
            if (current->size >= aligned_size + sizeof(block_header_t) + 8) {
                block_header_t* new_block = (block_header_t*)((char*)current + aligned_size);
                new_block->size = current->size - aligned_size;
                new_block->is_free = true;
                new_block->next = current->next;
                
                current->size = aligned_size;
                current->next = new_block;
            }
            
            // Mark as allocated
            current->is_free = false;
            
            // Remove from free list
            if (prev == NULL) {
                free_list = current->next;
            } else {
                prev->next = current->next;
            }
            
            current->next = NULL;
            
            // Return usable memory
            return get_usable_memory(current);
        }
        
        prev = current;
        current = current->next;
    }
    
    // No suitable block found
    return NULL;
}

// TODO: Implement mem_free() function
// This function should:
// 1. Find the block header for the given pointer
// 2. Mark the block as free
// 3. Add it back to the free list
// 4. (Optional) Consider merging with adjacent free blocks
void mem_free(void* ptr) {
    // Your implementation here...
    
    // Hint: Use get_block_header() to find the header
    // Hint: Consider where in the free list to insert this block
}

// Function to print the state of the memory pool
void print_memory_pool_state() {
    printf("Memory Pool State\n");
    printf("================\n");
    printf("Pool address: %p\n", memory_pool);
    printf("Pool size: %zu bytes\n", (size_t)POOL_SIZE);
    
    // Scan the entire memory pool for blocks
    block_header_t* current = (block_header_t*)memory_pool;
    int block_count = 0;
    
    printf("\nAll blocks:\n");
    while ((void*)current < (void*)((char*)memory_pool + POOL_SIZE)) {
        printf("Block %d: address=%p, size=%zu, is_free=%s\n",
               block_count++,
               (void*)current,
               current->size,
               current->is_free ? "true" : "false");
        
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
    
    printf("\n");
}

// Test function for mem_alloc and mem_free
void test_mem_alloc_and_free() {
    printf("Testing mem_alloc() and mem_free()\n");
    printf("================================\n\n");
    
    // Allocate some memory blocks
    printf("Allocating blocks...\n");
    void* ptr1 = mem_alloc(100);
    void* ptr2 = mem_alloc(200);
    void* ptr3 = mem_alloc(300);
    
    printf("Allocated 100 bytes at %p\n", ptr1);
    printf("Allocated 200 bytes at %p\n", ptr2);
    printf("Allocated 300 bytes at %p\n", ptr3);
    
    print_memory_pool_state();
    
    // Free the blocks
    printf("\nFreeing blocks...\n");
    
    printf("Freeing block at %p\n", ptr2);
    mem_free(ptr2);
    print_memory_pool_state();
    
    printf("Freeing block at %p\n", ptr1);
    mem_free(ptr1);
    print_memory_pool_state();
    
    printf("Freeing block at %p\n", ptr3);
    mem_free(ptr3);
    print_memory_pool_state();
    
    // Allocate again to test reuse
    printf("\nAllocating again to test reuse...\n");
    ptr1 = mem_alloc(50);
    printf("Allocated 50 bytes at %p\n", ptr1);
    print_memory_pool_state();
}

int main() {
    if (!init_memory_pool()) {
        printf("Failed to initialize memory pool!\n");
        return 1;
    }
    
    printf("Memory pool initialized successfully!\n\n");
    print_memory_pool_state();
    
    test_mem_alloc_and_free();
    
    return 0;
}
