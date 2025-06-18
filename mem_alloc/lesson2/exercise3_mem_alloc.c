#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <unistd.h>

/*
 * Exercise 3: Implement mem_alloc()
 * 
 * In this exercise, you'll implement a function that allocates memory
 * using the first-fit strategy.
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

// TODO: Implement mem_alloc() function
// This function should:
// 1. Search the free list for a block large enough to satisfy the request (first-fit)
// 2. If a suitable block is found, split it if necessary
// 3. Mark the block as allocated
// 4. Return a pointer to the usable memory
void* mem_alloc(size_t size) {
    // Your implementation here...
    
    // Hint: Don't forget to account for the header size when allocating
    // Hint: Consider alignment requirements
    
    return NULL;  // Replace with your implementation
}

// Function to print the state of the memory pool
void print_memory_pool_state() {
    printf("Memory Pool State\n");
    printf("================\n");
    printf("Pool address: %p\n", memory_pool);
    printf("Pool size: %zu bytes\n", (size_t)POOL_SIZE);
    
    block_header_t* current = free_list;
    int block_count = 0;
    
    printf("\nFree blocks:\n");
    while (current != NULL) {
        printf("Block %d: address=%p, size=%zu, is_free=%s\n",
               block_count++,
               (void*)current,
               current->size,
               current->is_free ? "true" : "false");
        current = current->next;
    }
    
    printf("\n");
}

// Test function for mem_alloc
void test_mem_alloc() {
    printf("Testing mem_alloc()\n");
    printf("==================\n\n");
    
    // Allocate some memory blocks
    void* ptr1 = mem_alloc(100);
    printf("Allocated 100 bytes at %p\n", ptr1);
    print_memory_pool_state();
    
    void* ptr2 = mem_alloc(200);
    printf("Allocated 200 bytes at %p\n", ptr2);
    print_memory_pool_state();
    
    void* ptr3 = mem_alloc(300);
    printf("Allocated 300 bytes at %p\n", ptr3);
    print_memory_pool_state();
}

int main() {
    if (!init_memory_pool()) {
        printf("Failed to initialize memory pool!\n");
        return 1;
    }
    
    printf("Memory pool initialized successfully!\n\n");
    print_memory_pool_state();
    
    test_mem_alloc();
    
    return 0;
}
