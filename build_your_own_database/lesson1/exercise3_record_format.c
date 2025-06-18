#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * Exercise 3: Design a Basic Record Format
 * 
 * This file contains skeleton code for implementing a basic record format
 * for storing data within database pages.
 *
 * Your task is to complete the implementation of the functions below.
 */

// Include the page structure from previous exercises
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

// Record header structure
typedef struct {
    uint16_t record_id;    // ID of the record within the page
    uint16_t record_size;  // Total size of the record in bytes
    uint16_t offset;       // Offset from the start of data area
    char flags;            // Record flags (e.g., deleted, overflow)
    char reserved;         // Reserved for future use
} RecordHeader;

// Slot directory structure
typedef struct {
    uint16_t n_slots;      // Number of slots in the directory
    RecordHeader slots[];  // Array of record headers (flexible array member)
} SlotDirectory;

// Forward declarations of functions from previous exercises
int page_init(Page *page, uint32_t page_id);
int page_free_space(const Page *page);

/**
 * Initialize a slot directory at the beginning of the page data area
 * 
 * @param page Pointer to the page
 * @return 0 on success, non-zero on failure
 */
int slot_directory_init(Page *page) {
    // TODO: Implement this function
    // 1. Check if page pointer is valid
    // 2. Initialize a slot directory at the beginning of the data area
    // 3. Update the free space pointer
    
    return 0;
}

/**
 * Get a pointer to the slot directory in a page
 * 
 * @param page Pointer to the page
 * @return Pointer to the slot directory, or NULL on error
 */
SlotDirectory *slot_directory_get(Page *page) {
    // TODO: Implement this function
    // 1. Check if page pointer is valid
    // 2. Return a pointer to the slot directory
    
    return NULL;
}

/**
 * Insert a record into a page
 * 
 * @param page Pointer to the page
 * @param data Pointer to the record data
 * @param data_size Size of the record data in bytes
 * @return Record ID on success, -1 on failure
 */
int record_insert(Page *page, const void *data, uint16_t data_size) {
    // TODO: Implement this function
    // 1. Check if there's enough free space in the page
    // 2. Get the slot directory
    // 3. Add a new slot to the directory
    // 4. Copy the record data to the appropriate location
    // 5. Update the free space pointer
    // 6. Increment the record count
    // 7. Return the new record ID
    
    return -1;
}

/**
 * Retrieve a record from a page
 * 
 * @param page Pointer to the page
 * @param record_id ID of the record to retrieve
 * @param data_out Buffer to store the record data (can be NULL to just get the size)
 * @param max_size Maximum size of the output buffer
 * @return Size of the record on success, -1 on failure
 */
int record_get(const Page *page, uint16_t record_id, void *data_out, uint16_t max_size) {
    // TODO: Implement this function
    // 1. Check if page pointer is valid
    // 2. Get the slot directory
    // 3. Check if the record_id is valid
    // 4. Get the record header from the slot directory
    // 5. If data_out is not NULL, copy the record data to the output buffer
    // 6. Return the size of the record
    
    return -1;
}

/**
 * Delete a record from a page (mark as deleted)
 * 
 * @param page Pointer to the page
 * @param record_id ID of the record to delete
 * @return 0 on success, non-zero on failure
 */
int record_delete(Page *page, uint16_t record_id) {
    // TODO: Implement this function
    // 1. Check if page pointer is valid
    // 2. Get the slot directory
    // 3. Check if the record_id is valid
    // 4. Mark the record as deleted by setting the appropriate flag
    // Note: This doesn't reclaim the space, just marks it as deleted
    
    return 0;
}

/**
 * Print information about all records in a page
 * 
 * @param page Pointer to the page
 */
void page_print_records(const Page *page) {
    // TODO: Implement this function
    // 1. Check if page pointer is valid
    // 2. Get the slot directory
    // 3. Iterate through all slots and print record information
    
    printf("Page ID: %u, Records: %u\n", page->header.page_id, page->header.n_records);
    printf("Free space: %d bytes\n", page_free_space(page));
    
    // Print record details here...
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
    
    // Initialize the slot directory
    if (slot_directory_init(page) != 0) {
        printf("Failed to initialize slot directory\n");
        free(page);
        return 1;
    }
    
    // Insert some test records
    const char *test_data[] = {
        "This is the first record",
        "This is the second record with more data",
        "This is the third record with even more data than the previous ones"
    };
    
    for (int i = 0; i < 3; i++) {
        int record_id = record_insert(page, test_data[i], strlen(test_data[i]) + 1);
        if (record_id < 0) {
            printf("Failed to insert record %d\n", i);
        } else {
            printf("Inserted record with ID: %d\n", record_id);
        }
    }
    
    // Print all records
    page_print_records(page);
    
    // Retrieve and print a specific record
    char buffer[256];
    int record_id = 1;  // Get the second record
    int size = record_get(page, record_id, buffer, sizeof(buffer));
    
    if (size >= 0) {
        printf("Retrieved record %d: '%s' (size: %d bytes)\n", record_id, buffer, size);
    } else {
        printf("Failed to retrieve record %d\n", record_id);
    }
    
    // Delete a record
    record_id = 0;  // Delete the first record
    if (record_delete(page, record_id) == 0) {
        printf("Deleted record %d\n", record_id);
    } else {
        printf("Failed to delete record %d\n", record_id);
    }
    
    // Print records again to verify deletion
    page_print_records(page);
    
    // Clean up
    free(page);
    return 0;
}
