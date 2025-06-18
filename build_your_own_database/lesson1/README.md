# Lesson 1: Database Fundamentals and Storage Engine Basics

## Theoretical Background

### Database Architecture Overview

A database management system (DBMS) typically consists of several key components:

1. **Storage Engine**: Manages how data is stored on disk and retrieved
2. **Buffer Manager**: Handles caching of disk pages in memory
3. **Query Processor**: Parses, optimizes, and executes queries
4. **Transaction Manager**: Ensures ACID properties
5. **Recovery Manager**: Handles crash recovery
6. **Concurrency Control**: Manages simultaneous access

In this lesson, we focus on the storage engine, which is the foundation of any database system.

### Storage Models

Databases typically use one of two storage models:

1. **Row-based storage**: Stores all columns of a row together
   - Efficient for retrieving entire records
   - Used in OLTP (Online Transaction Processing) systems
   - Examples: MySQL (InnoDB), PostgreSQL

2. **Column-based storage**: Stores each column separately
   - Efficient for analytical queries that access few columns but many rows
   - Used in OLAP (Online Analytical Processing) systems
   - Examples: Vertica, Redshift

For our basic RDBMS, we'll implement a row-based storage model.

### Page-Based Storage

Most databases organize data in fixed-size blocks called **pages**:

- Typical page sizes range from 4KB to 16KB
- Pages are the unit of transfer between disk and memory
- Pages may contain:
  - Header information (page ID, checksum, etc.)
  - Data records
  - Free space tracking
  - Pointers to other pages

### Disk vs. Memory Considerations

When designing a storage engine, we must consider:

- **Disk access patterns**: Sequential access is much faster than random access
- **Block alignment**: Aligning data to disk blocks improves I/O performance
- **Caching**: Frequently accessed pages should stay in memory
- **Persistence**: Data must survive system crashes

## Exercises

### Exercise 1: Create a Simple Page Structure

**Objective**: Design and implement a basic page structure that can store records.

**Tasks**:
1. Define a page structure with a header and data area
2. Implement functions to initialize a new page
3. Create functions to check available space in a page

**Hints**:
- Use a fixed-size array or allocated memory block to represent a page
- Include metadata like page ID, free space pointer, and checksum
- Consider alignment requirements for efficient memory access

**Example Structure**:
```c
#define PAGE_SIZE 4096  // 4KB pages
#define PAGE_HEADER_SIZE 128

typedef struct {
    uint32_t page_id;       // Unique identifier for the page
    uint32_t free_space;    // Offset to the start of free space
    uint16_t n_records;     // Number of records in the page
    uint16_t checksum;      // For data integrity verification
    // Other header information...
    char reserved[116];     // Padding to align to desired header size
} PageHeader;

typedef struct {
    PageHeader header;
    char data[PAGE_SIZE - PAGE_HEADER_SIZE];  // Data area
} Page;
```

### Exercise 2: Implement Basic File I/O Operations

**Objective**: Create functions to read and write pages to disk.

**Tasks**:
1. Implement a function to create a new database file
2. Write functions to read a page from disk into memory
3. Create functions to write a page from memory to disk
4. Implement basic error handling for I/O operations

**Hints**:
- Use `fopen`, `fread`, `fwrite`, and `fseek` for file operations
- Calculate file offsets based on page IDs
- Consider using `O_DIRECT` flag (or equivalent) to bypass OS caching for advanced implementations
- Implement proper error handling for I/O failures

**Example Functions**:
```c
// Function prototypes
int db_create_file(const char *filename);
int db_read_page(FILE *file, uint32_t page_id, Page *page);
int db_write_page(FILE *file, uint32_t page_id, const Page *page);
```

### Exercise 3: Design a Basic Record Format

**Objective**: Create a record format that can store data within pages.

**Tasks**:
1. Define a record header structure
2. Implement functions to insert a record into a page
3. Create functions to retrieve a record from a page
4. Add support for variable-length records (optional)

**Hints**:
- Include record length and possibly a record ID in the header
- For simplicity, start with fixed-length records
- Consider using a slot directory approach for variable-length records
- Think about record alignment requirements

**Example Structure**:
```c
typedef struct {
    uint16_t record_id;    // ID of the record within the page
    uint16_t record_size;  // Total size of the record in bytes
    uint16_t offset;       // Offset from the start of data area
    char flags;            // Record flags (e.g., deleted, overflow)
    char reserved;         // Reserved for future use
} RecordHeader;

// For the slot directory approach
typedef struct {
    uint16_t n_slots;      // Number of slots in the directory
    RecordHeader slots[];  // Array of record headers
} SlotDirectory;
```

## Milestone Project: Simple Record Store

Combine the exercises above to create a program that can:
1. Create a database file
2. Add records to pages
3. Retrieve records by ID
4. List all records in a page

This will form the foundation of your storage engine.

## Testing Your Implementation

Create test cases to verify:
1. Pages are correctly written to and read from disk
2. Records can be inserted and retrieved accurately
3. The system handles edge cases (full pages, empty pages)
4. Data integrity is maintained

## Thinking Questions

1. How would your implementation change if you needed to support records larger than a page?
2. What are the trade-offs between different page sizes?
3. How might you implement record deletion without immediately reclaiming the space?
4. What would be required to make your storage engine crash-resistant?

## Next Steps

After completing this lesson, you'll have a basic understanding of how databases store and retrieve data at the lowest level. In the next lesson, we'll build on this by implementing a buffer pool to efficiently manage memory and reduce disk I/O operations.

## Resources

- "Database System Concepts" by Silberschatz, Korth, and Sudarshan (Chapter on Storage and File Structure)
- SQLite Documentation on the B-tree file format
- PostgreSQL Documentation on the page layout

## Glossary

- **Page**: Fixed-size block of data, the unit of I/O operations
- **Record**: A single entry in the database, typically representing one row
- **Slot Directory**: A technique for managing variable-length records within a page
- **OLTP**: Online Transaction Processing - systems optimized for transaction processing
- **OLAP**: Online Analytical Processing - systems optimized for complex queries and analysis
