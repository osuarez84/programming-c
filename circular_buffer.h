#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <pthread.h>


typedef struct {
    int* buffer;        // the buffer array
    size_t head;        // index of the first element
    size_t tail;        // index where next element will be inserted
    size_t capacity;    // max number of elements that can be stored
    size_t size;        // current number of elements in the buffer
    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} CircularBuffer;


bool cb_is_full(const CircularBuffer* cb);
bool cb_is_empty(const CircularBuffer* cb);
void cb_free(CircularBuffer* cb);
CircularBuffer* cb_init(size_t capacity);
bool cb_push(CircularBuffer* cb, int item);
bool cb_pop(CircularBuffer* cb, int* value);

#endif