#include <stdio.h>
#include <stdlib.h>


int global_initialized = 42;
int global_uninitialized;


// function to demonstrate text segment
void function_example() {
    printf(" Address of function_example(): %p\n", (void*)function_example);
}



int main() {
    int local_var = 10;
    int another_local = 20;

    int* heap_var = malloc(sizeof(int));
    *heap_var = 30;

    printf("----- Memory Segment Exploration -----\n\n");

    // stack segment
    printf("Stack segment:\n");
    printf(" Address of local_var: %p\n", (void*)&local_var);
    printf(" Address of another_local: %p\n", (void*)&another_local);
    

    // heap segment
    printf("\nHeap segment:\n");
    printf(" Address of heap_var: %p\n", (void*)heap_var);

    // data segment (initialized)
    printf("\nInitialized Data segment\n");
    printf(" Address of global_initialized: %p\n", (void*) &global_initialized);

    // BSS segment (uninitialized)
    printf("\nUninitialized Data segment (BSS)\n");
    printf(" Address of global_uninitialized: %p\n", (void*)&global_uninitialized);

    // Text segment
    printf("\nText Segment\n");
    printf(" Address of main function: %p\n", (void*)main);
    function_example();
}