#include <stdio.h>
#include <stdlib.h>

// Global variables (data segment)
int global_initialized = 42;    // Initialized data segment
int global_uninitialized;       // Uninitialized data segment (BSS)

// Function to demonstrate text segment
void function_example() {
    // This function's code is in the text segment
    printf("Address of function_example(): %p\n", (void*)function_example);
}

int main() {
    // Local variables (stack)
    int local_var = 10;
    int another_local = 20;
    
    // Dynamic memory allocation (heap)
    int *heap_var = (int*)malloc(sizeof(int));
    *heap_var = 30;
    
    // Print addresses of variables in different segments
    printf("\n--- Memory Segment Exploration ---\n\n");
    
    // Stack segment
    printf("Stack Segment:\n");
    printf("  Address of local_var: %p\n", (void*)&local_var);
    printf("  Address of another_local: %p\n", (void*)&another_local);
    
    // Heap segment
    printf("\nHeap Segment:\n");
    printf("  Address of heap_var: %p\n", (void*)heap_var);
    
    // Data segment (initialized)
    printf("\nInitialized Data Segment:\n");
    printf("  Address of global_initialized: %p\n", (void*)&global_initialized);
    
    // BSS segment (uninitialized)
    printf("\nUninitialized Data Segment (BSS):\n");
    printf("  Address of global_uninitialized: %p\n", (void*)&global_uninitialized);
    
    // Text segment
    printf("\nText Segment:\n");
    printf("  Address of main function: %p\n", (void*)main);
    function_example();
    
    // Clean up
    free(heap_var);
    
    printf("\n--- Memory Layout Analysis ---\n");
    printf("Notice how:\n");
    printf("1. Stack variables are at high addresses\n");
    printf("2. Heap variables are at lower addresses than stack\n");
    printf("3. Global variables (data/BSS) are at even lower addresses\n");
    printf("4. Code (text) is typically at the lowest addresses\n");
    
    return 0;
}
