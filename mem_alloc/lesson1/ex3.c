#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>




int main() {
    printf("----- mmap() Memory allocation example -----\n");

    // Allocate memory using mmap
    void* memory = mmap(
        NULL,
        (size_t)4096,
        PROT_READ | PROT_WRITE, // allow reading and writing
        MAP_ANONYMOUS | MAP_PRIVATE, // not backed by a file, private to this process
        -1,
        0
    );

    if (memory == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    printf("Memory allocated at address: %p\n", memory);

    // write data to the allocated memory
    const char* message = "Hello from mmap allocated memory";
    strcpy((char*)memory, message);

    // read data from the allocated memory
    printf("Memory contains: %s\n", (char*)memory);

    // demonstrate memory access at different offsets
    printf("Accessing memory at different offsets:\n");

    // write integers at different offsets
    int* int_ptr = (int*)(memory+104);
    *int_ptr = 100;

    // read back the integers
    printf("Integer at offset 100: %d\n", *(int*)(memory + 100));
    printf("Integer at offset 104: %d\n", *(int*)(memory+104));

    // release the memory when done
    if(munmap(memory, (size_t)4096) == -1) {
        perror("munmap failed");
        return 1;
    }
    printf("Memory successfully unmapped\n");
    return 0;
}