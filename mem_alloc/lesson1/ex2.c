#include <stdio.h>
#include <unistd.h>
#include <string.h>




// sbrk() is the traditional way to extend programs data space (heap)

void write_to_memory(void* memory, const char* message) {
    strcpy((char*)memory, message);
}

void read_from_memory(void* memory) {
    printf("Memory contains: %s\n", (char*)memory);
}

int main() {
    printf("----- sbrk() Memory allocation example -----\n");


    // get the current program break (end of data segment)
    // for that we increment in zero
    void* initial_break = sbrk(0);
    printf("Initial program break: %p\n", initial_break);


    // request 100 bytes of memory using sbrk()
    intptr_t inc = 100;
    void* memory = sbrk(inc);

    // check errors when requesting memory
    if (memory == (void*)-1) {
        perror("sbrk failed");
        return 1;
    }

    // verify the new program break
    // get the end of the current data segment
    void* new_break = sbrk(0);
    printf("New program break: %p\n", new_break);
    printf("Size of a char is: %ld bytes\n", sizeof(char));
    printf("Size of an int is: %ld bytes\n", sizeof(int));
    // cast the void* to char because sizeof(char) = 1 byte
    printf("Difference: %ld bytes\n", (char*)new_break - (char*)initial_break);

    // write data to the allocated memory
    const char* message = "Hello from the other side!";
    write_to_memory(memory, message);

    // read data from the allocated memory
    printf("Reading from allocated memory:\n");
    read_from_memory(memory);

    // demonstrate memory persistence across function calls
    printf("Demostrating memory persistence across function calls\n");
    read_from_memory(memory);


    // we would need to explicitly release the memory
    intptr_t dec = -100;
    void* release_break = sbrk(dec);
    if (release_break == (void*)-1) {
        perror("sbrk failed");
        return 1;
    }
    void* new_release_break = sbrk(0);
    printf("New program break after releasing 100 bytes of memory: %p\n", new_release_break);

    return 0;
}