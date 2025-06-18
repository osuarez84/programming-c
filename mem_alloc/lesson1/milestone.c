#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

#define FREE 1
#define NOT_FREE 0


typedef struct block_t {
    size_t size;
    int free; // 0 if allocated, 1 if free
    struct block_t* next;
} Block_t;


Block_t* mem_chunk(size_t size) {
    // this gives us 4046 bytes of raw memory
    Block_t* memory = mmap(
        NULL,
        size + sizeof(Block_t),
        PROT_READ | PROT_WRITE,
        MAP_ANONYMOUS | MAP_PRIVATE,
        -1,
        0
    );
    if(memory == MAP_FAILED) {
        perror("mmap failed");
        return NULL;
    }

    // the header of the block is at the beginning
    // because we said so when organizing the struct
    Block_t* block = (Block_t*)memory;
    block->size = size;
    block->free = FREE;
    block->next = NULL;

    return block;
}

// maintain a linked list of nodes with the info of all the 
// used blocks
Block_t* insert_at_the_end(Block_t* head, Block_t* new_chunk) {
    Block_t* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_chunk;
    return head;
}

// get pointer to usable memory from a block
void* get_usable_memory(Block_t* block) {
    return (void*)(block + 1);
}

void iterate_over_all(Block_t* head) {
    Block_t* current = head;

    int count = 0;
    while (current != NULL) {
        void* usable = get_usable_memory(current);
        printf("Node %d\n", count);
        printf("Block header address: %p\n", (void*)current);
        printf("Usable memory address: %p\n", usable);
        printf("Size: %zu\n", current->size);
        printf("Real size of the usable memory: %zu\n", current->size - sizeof(Block_t));
        printf("Is it free?: %d\n", current->free);
        current = current->next;
        count++;
    }
    return;
}



int main() {
    size_t size = 4096;
    Block_t* head = mem_chunk(size);
    Block_t* chunk_alloc2 = mem_chunk(size);
    Block_t* chunk_alloc3 = mem_chunk(size);

    insert_at_the_end(head, chunk_alloc2);
    insert_at_the_end(head, chunk_alloc3);

    iterate_over_all(head);

    return 0;
}