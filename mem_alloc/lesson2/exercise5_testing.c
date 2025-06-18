#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <assert.h>

/*
 * Exercise 5: Write Tests for Your Memory Allocator
 * 
 * In this exercise, you'll create comprehensive tests for your
 * memory allocator to verify that it works correctly.
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

// TODO: Copy your mem_alloc implementation here
void* mem_alloc(size_t size) {
    // Your implementation here...
    return NULL;
}

// TODO: Copy your mem_free implementation here
void mem_free(void* ptr) {
    // Your implementation here...
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
    
    printf("\nMemory usage summary:\n");
    printf("Total allocated: %zu bytes\n", total_allocated);
    printf("Total free: %zu bytes\n", total_free);
    printf("Total: %zu bytes\n", total_allocated + total_free);
    
    printf("\n");
}

// Test 1: Basic allocation and deallocation
void test_basic_alloc_free() {
    printf("\nTest 1: Basic Allocation and Deallocation\n");
    printf("=======================================\n");
    
    // Allocate a block
    void* ptr = mem_alloc(100);
    printf("Allocated 100 bytes at %p\n", ptr);
    mem_dump();
    
    // Free the block
    printf("Freeing memory at %p\n", ptr);
    mem_free(ptr);
    mem_dump();
    
    // Verify that the block is now free
    // TODO: Add your verification code here
}

// Test 2: Multiple allocations and deallocations
void test_multiple_alloc_free() {
    printf("\nTest 2: Multiple Allocations and Deallocations\n");
    printf("===========================================\n");
    
    // Allocate multiple blocks
    void* ptr1 = mem_alloc(100);
    void* ptr2 = mem_alloc(200);
    void* ptr3 = mem_alloc(300);
    
    printf("Allocated 100 bytes at %p\n", ptr1);
    printf("Allocated 200 bytes at %p\n", ptr2);
    printf("Allocated 300 bytes at %p\n", ptr3);
    mem_dump();
    
    // Free in a different order
    printf("Freeing memory at %p\n", ptr2);
    mem_free(ptr2);
    mem_dump();
    
    printf("Freeing memory at %p\n", ptr1);
    mem_free(ptr1);
    mem_dump();
    
    printf("Freeing memory at %p\n", ptr3);
    mem_free(ptr3);
    mem_dump();
    
    // TODO: Add your verification code here
}

// Test 3: Memory reuse
void test_memory_reuse() {
    printf("\nTest 3: Memory Reuse\n");
    printf("==================\n");
    
    // Allocate and free to create free blocks
    void* ptr1 = mem_alloc(100);
    void* ptr2 = mem_alloc(200);
    
    printf("Allocated 100 bytes at %p\n", ptr1);
    printf("Allocated 200 bytes at %p\n", ptr2);
    
    printf("Freeing memory at %p\n", ptr1);
    mem_free(ptr1);
    mem_dump();
    
    // Allocate again and verify reuse
    void* ptr3 = mem_alloc(50);
    printf("Allocated 50 bytes at %p\n", ptr3);
    mem_dump();
    
    // TODO: Add your verification code here
    // Check if ptr3 reuses the space from ptr1
    
    // Clean up
    mem_free(ptr2);
    mem_free(ptr3);
}

// Test 4: Edge cases
void test_edge_cases() {
    printf("\nTest 4: Edge Cases\n");
    printf("================\n");
    
    // Test allocating zero bytes
    void* ptr1 = mem_alloc(0);
    printf("Allocated 0 bytes: %p\n", ptr1);
    
    // Test allocating a very large block
    void* ptr2 = mem_alloc(POOL_SIZE * 2);
    printf("Allocated %zu bytes (larger than pool): %p\n", POOL_SIZE * 2, ptr2);
    
    // Test freeing NULL
    printf("Freeing NULL pointer\n");
    mem_free(NULL);
    
    // Clean up any valid allocations
    if (ptr1 != NULL) mem_free(ptr1);
    if (ptr2 != NULL) mem_free(ptr2);
    
    mem_dump();
}

// Test 5: Fragmentation handling
void test_fragmentation() {
    printf("\nTest 5: Fragmentation Handling\n");
    printf("============================\n");
    
    // Create a fragmented memory state
    void* ptrs[10];
    
    // Allocate 10 blocks
    for (int i = 0; i < 10; i++) {
        ptrs[i] = mem_alloc(100);
        printf("Allocated 100 bytes at %p\n", ptrs[i]);
    }
    
    // Free every other block to create fragmentation
    for (int i = 0; i < 10; i += 2) {
        printf("Freeing memory at %p\n", ptrs[i]);
        mem_free(ptrs[i]);
    }
    
    mem_dump();
    
    // Try to allocate a block larger than the individual fragments
    void* large_ptr = mem_alloc(150);
    printf("Allocated 150 bytes at %p\n", large_ptr);
    mem_dump();
    
    // Clean up
    for (int i = 1; i < 10; i += 2) {
        mem_free(ptrs[i]);
    }
    if (large_ptr != NULL) mem_free(large_ptr);
}

int main() {
    if (!init_memory_pool()) {
        printf("Failed to initialize memory pool!\n");
        return 1;
    }
    
    printf("Memory pool initialized successfully!\n\n");
    mem_dump();
    
    // Run tests
    test_basic_alloc_free();
    
    // Reset the memory pool for the next test
    if (!init_memory_pool()) {
        printf("Failed to reinitialize memory pool!\n");
        return 1;
    }
    test_multiple_alloc_free();
    
    if (!init_memory_pool()) return 1;
    test_memory_reuse();
    
    if (!init_memory_pool()) return 1;
    test_edge_cases();
    
    if (!init_memory_pool()) return 1;
    test_fragmentation();
    
    printf("\nAll tests completed!\n");
    
    return 0;
}
