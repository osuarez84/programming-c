# Database System Architecture

Below is a diagram showing the major components of the database system you'll be building throughout this project. The diagram illustrates how these components interact with each other and the flow of data through the system.

```mermaid
graph TD
    %% Client Interface
    Client[Client Application] --> SQLInterface[SQL Interface]
    
    %% Query Processing
    SQLInterface --> QueryParser[Query Parser]
    QueryParser --> QueryOptimizer[Query Optimizer]
    QueryOptimizer --> QueryExecutor[Query Executor]
    
    %% Access Methods
    QueryExecutor --> IndexManager[Index Manager]
    QueryExecutor --> TableManager[Table Manager]
    
    %% Storage Engine Components
    IndexManager --> BTreeIndex[B-Tree Index]
    TableManager --> RecordManager[Record Manager]
    BTreeIndex --> BufferManager
    RecordManager --> BufferManager[Buffer Manager]
    
    %% Buffer Management
    BufferManager --> PageManager[Page Manager]
    BufferManager --> ReplacementPolicy[Replacement Policy]
    
    %% Disk Storage
    PageManager --> DiskManager[Disk Manager]
    
    %% Transaction Management
    QueryExecutor --> TransactionManager[Transaction Manager]
    TransactionManager --> LockManager[Lock Manager]
    TransactionManager --> LogManager[Log Manager]
    
    %% Recovery System
    LogManager --> RecoveryManager[Recovery Manager]
    RecoveryManager --> DiskManager
    
    %% File System
    DiskManager --> FileSystem[File System]
    
    %% Component Descriptions with better contrast
    classDef lesson1 fill:#f9d5e5,stroke:#000,stroke-width:2px,color:#000,font-weight:bold
    classDef lesson2 fill:#eeeeee,stroke:#000,stroke-width:2px,color:#000,font-weight:bold
    classDef lesson3 fill:#d5f9e5,stroke:#000,stroke-width:2px,color:#000,font-weight:bold
    classDef lesson4 fill:#e5d5f9,stroke:#000,stroke-width:2px,color:#000,font-weight:bold
    classDef lesson5 fill:#f9e5d5,stroke:#000,stroke-width:2px,color:#000,font-weight:bold
    classDef lesson6 fill:#d5e5f9,stroke:#000,stroke-width:2px,color:#000,font-weight:bold
    classDef lesson7 fill:#f9f9d5,stroke:#000,stroke-width:2px,color:#000,font-weight:bold
    classDef lesson8 fill:#d5f9f9,stroke:#000,stroke-width:2px,color:#000,font-weight:bold
    classDef lesson9 fill:#f9d5f9,stroke:#000,stroke-width:2px,color:#000,font-weight:bold
    classDef lesson10 fill:#d5d5d5,stroke:#000,stroke-width:2px,color:#000,font-weight:bold
    
    %% Apply classes to nodes based on which lesson they belong to
    class DiskManager,PageManager,RecordManager lesson1
    class BufferManager,ReplacementPolicy lesson2
    class BTreeIndex,IndexManager lesson3
    class TableManager,RecordManager lesson4
    class QueryParser,QueryExecutor lesson5
    class QueryOptimizer lesson6
    class TransactionManager,LockManager lesson7
    class LogManager,RecoveryManager lesson8
    class SQLInterface,Client lesson9
    class FileSystem lesson10
```

## Component Descriptions

### Lesson 1: Database Fundamentals and Storage Engine
- **Disk Manager**: Handles reading and writing pages to disk
- **Page Manager**: Manages page structure and layout
- **Record Manager**: Handles record storage within pages

### Lesson 2: Buffer Pool Management
- **Buffer Manager**: Caches pages in memory to reduce disk I/O
- **Replacement Policy**: Implements algorithms like LRU for page eviction

### Lesson 3: B-Tree Indexes
- **B-Tree Index**: Implements B-Tree data structure for efficient lookups
- **Index Manager**: Manages creation and maintenance of indexes

### Lesson 4: Table and Record Management
- **Table Manager**: Handles table metadata and schema
- **Record Manager**: Manages record formats and operations

### Lesson 5: Query Processing Basics
- **Query Parser**: Parses SQL into internal representation
- **Query Executor**: Executes query plans

### Lesson 6: Query Optimization
- **Query Optimizer**: Selects efficient execution plans

### Lesson 7: Transaction Management
- **Transaction Manager**: Ensures ACID properties
- **Lock Manager**: Handles concurrency control

### Lesson 8: Recovery System
- **Log Manager**: Manages write-ahead logging
- **Recovery Manager**: Handles crash recovery

### Lesson 9: SQL Interface
- **SQL Interface**: Provides SQL API to clients
- **Client Application**: End-user application

### Lesson 10: System Integration
- **File System**: Underlying OS file system

## Data Flow

1. Client sends SQL query to SQL Interface
2. Query Parser converts SQL to internal representation
3. Query Optimizer selects efficient execution plan
4. Query Executor runs the plan using access methods
5. Access methods retrieve data through Buffer Manager
6. Buffer Manager fetches pages from disk if not in memory
7. Transaction Manager ensures ACID properties
8. Log Manager records changes for recovery
9. Results flow back up to the client

This architecture represents a simplified but complete database system. As you progress through the lessons, you'll build each component and understand how they work together.
