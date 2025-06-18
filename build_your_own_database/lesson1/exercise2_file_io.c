#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 * Exercise 2: Implement Basic File I/O Operations
 * 
 * This file contains skeleton code for implementing basic file I/O operations
 * for reading and writing database pages to disk.
 *
 * Your task is to complete the implementation of the functions below.
 */

// Include the page structure from exercise 1
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

// Forward declaration of functions from exercise 1
int page_init(Page *page, uint32_t page_id);
uint16_t page_calculate_checksum(const Page *page);

/**
 * Create a new database file with the specified number of pages
 * 
 * @param filename Name of the database file to create
 * @param num_pages Number of pages to initialize in the file
 * @return 0 on success, non-zero on failure
 */
int db_create_file(const char *filename, uint32_t num_pages) {
    // TODO: Implement this function
    // 1. Open the file for writing
    // 2. Create and initialize the specified number of pages
    // 3. Write the pages to the file
    // 4. Close the file
    
    return 0;
}

/**
 * Open an existing database file
 * 
 * @param filename Name of the database file to open
 * @param mode File mode ("r" for read, "w" for write, "r+" for read/write)
 * @return File pointer on success, NULL on failure
 */
FILE *db_open_file(const char *filename, const char *mode) {
    // TODO: Implement this function
    // 1. Open the file with the specified mode
    // 2. Check for errors
    // 3. Return the file pointer
    
    return NULL;
}

/**
 * Read a page from the database file into memory
 * 
 * @param file File pointer to the database file
 * @param page_id ID of the page to read
 * @param page Pointer to the page structure to populate
 * @return 0 on success, non-zero on failure
 */
int db_read_page(FILE *file, uint32_t page_id, Page *page) {
    // TODO: Implement this function
    // 1. Calculate the offset in the file based on page_id
    // 2. Seek to that position
    // 3. Read the page data
    // 4. Verify the page checksum
    // 5. Return appropriate status code
    
    return 0;
}

/**
 * Write a page from memory to the database file
 * 
 * @param file File pointer to the database file
 * @param page_id ID of the page to write
 * @param page Pointer to the page structure to write
 * @return 0 on success, non-zero on failure
 */
int db_write_page(FILE *file, uint32_t page_id, const Page *page) {
    // TODO: Implement this function
    // 1. Update the page checksum before writing
    // 2. Calculate the offset in the file based on page_id
    // 3. Seek to that position
    // 4. Write the page data
    // 5. Flush changes to disk
    // 6. Return appropriate status code
    
    return 0;
}

/**
 * Close the database file
 * 
 * @param file File pointer to close
 * @return 0 on success, non-zero on failure
 */
int db_close_file(FILE *file) {
    // TODO: Implement this function
    // 1. Check if the file pointer is valid
    // 2. Close the file
    // 3. Return appropriate status code
    
    return 0;
}

// Main function for testing
int main() {
    const char *filename = "test_database.db";
    uint32_t num_pages = 10;
    
    // Create a new database file
    printf("Creating database file with %u pages...\n", num_pages);
    if (db_create_file(filename, num_pages) != 0) {
        printf("Failed to create database file\n");
        return 1;
    }
    
    // Open the database file
    FILE *file = db_open_file(filename, "r+");
    if (!file) {
        printf("Failed to open database file\n");
        return 1;
    }
    
    // Create a test page
    Page test_page;
    if (page_init(&test_page, 5) != 0) {
        printf("Failed to initialize test page\n");
        db_close_file(file);
        return 1;
    }
    
    // Write the test page to the file
    printf("Writing test page (ID: %u) to database file...\n", test_page.header.page_id);
    if (db_write_page(file, test_page.header.page_id, &test_page) != 0) {
        printf("Failed to write test page to database file\n");
        db_close_file(file);
        return 1;
    }
    
    // Read the test page back from the file
    Page read_page;
    printf("Reading test page (ID: %u) from database file...\n", test_page.header.page_id);
    if (db_read_page(file, test_page.header.page_id, &read_page) != 0) {
        printf("Failed to read test page from database file\n");
        db_close_file(file);
        return 1;
    }
    
    // Verify the page was read correctly
    if (read_page.header.page_id == test_page.header.page_id) {
        printf("Successfully read page with ID: %u\n", read_page.header.page_id);
    } else {
        printf("Page ID mismatch: expected %u, got %u\n", 
               test_page.header.page_id, read_page.header.page_id);
    }
    
    // Close the database file
    db_close_file(file);
    
    return 0;
}
