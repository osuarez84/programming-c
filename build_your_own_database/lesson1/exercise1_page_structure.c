#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/*
 * Exercise 1: Create a Simple Page Structure
 * 
 * This file contains skeleton code for implementing a basic page structure
 * that will serve as the foundation for our database storage engine.
 *
 * Your task is to complete the implementation of the functions below.
 */

#define PAGE_SIZE 4096       // 4KB pages
#define PAGE_HEADER_SIZE 128 // Size of the page header

// Page header structure
typedef struct {
    uint32_t page_id;       // Unique identifier for the page
    uint32_t free_space;    // Offset to the start of free space
    uint16_t n_records;     // Number of records in the page
    uint16_t checksum;      // For data integrity verification
    // Other header information...
    char reserved[116];     // Padding to align to desired header size
} PageHeader;

// Page structure
typedef struct {
    PageHeader header;
    char data[PAGE_SIZE - PAGE_HEADER_SIZE];  // Data area
} Page;

/**
 * Initialize a new page with the given page ID
 * 
 * @param page Pointer to the page to initialize
 * @param page_id Unique identifier for the page
 * @return 0 on success, non-zero on failure
 */
int page_init(Page *page, uint32_t page_id) {
    // TODO: Implement this function
    // 1. Check if page pointer is valid
    // 2. Initialize the page header fields
    // 3. Set the free space pointer to the beginning of the data area
    // 4. Calculate and set the checksum
    
    return 0;
}

/**
 * Calculate how much free space is available in the page
 * 
 * @param page Pointer to the page
 * @return Number of bytes of free space available, or -1 on error
 */
int page_free_space(const Page *page) {
    // TODO: Implement this function
    // 1. Check if page pointer is valid
    // 2. Calculate free space by subtracting the free space offset from the total data area size
    
    return 0;
}

/**
 * Calculate a simple checksum for the page header
 * 
 * @param page Pointer to the page
 * @return Calculated checksum value
 */
uint16_t page_calculate_checksum(const Page *page) {
    // TODO: Implement this function
    // 1. Implement a simple checksum algorithm
    // 2. Consider using XOR or a simple sum of header values
    // Note: In a real database, you would use a more robust algorithm
    
    return 0;
}

/**
 * Verify the page's checksum to detect corruption
 * 
 * @param page Pointer to the page
 * @return 1 if checksum is valid, 0 if invalid
 */
int page_verify_checksum(const Page *page) {
    // TODO: Implement this function
    // 1. Calculate the checksum
    // 2. Compare with the stored checksum
    
    return 0;
}

/**
 * Print page information for debugging
 * 
 * @param page Pointer to the page
 */
void page_debug_print(const Page *page) {
    // TODO: Implement this function
    // Print relevant page information for debugging purposes
    
    printf("Page ID: %u\n", page->header.page_id);
    printf("Free space offset: %u\n", page->header.free_space);
    printf("Number of records: %u\n", page->header.n_records);
    printf("Checksum: %u\n", page->header.checksum);
    printf("Free space available: %d bytes\n", page_free_space(page));
}

// Main function for testing
int main() {
    // Create a new page
    Page *page = (Page *)malloc(sizeof(Page));
    if (!page) {
        printf("Failed to allocate memory for page\n");
        return 1;
    }
    
    // Initialize the page
    if (page_init(page, 1) != 0) {
        printf("Failed to initialize page\n");
        free(page);
        return 1;
    }
    
    // Print page information
    page_debug_print(page);
    
    // Clean up
    free(page);
    return 0;
}
