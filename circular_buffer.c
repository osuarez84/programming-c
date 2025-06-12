#include "circular_buffer.h"

CircularBuffer* cb_init(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }
    CircularBuffer* buff = malloc(sizeof(CircularBuffer));
    if (buff == NULL) {
        fprintf(stderr, "Failed to allocate memory for the struct object\n");
        return NULL;
    }

    buff->buffer = malloc(sizeof(int) * capacity);
    if (buff->buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory for the buffer\n");
        free(buff);
        return NULL;
    }

    // init synchronization primitives
    if (pthread_mutex_init(&buff->mutex, NULL) != 0) {
        free(buff->buffer);
        free(buff);
        return NULL;
    }

    if (pthread_cond_init(&buff->not_full, NULL) != 0 || 
        pthread_cond_init(&buff->not_empty, NULL) != 0) {
            pthread_mutex_destroy(&buff->mutex);
            free(buff->buffer);
            free(buff);
            return NULL;
        }

    buff->head = 0; // tail and head are used as indexes to the array
    buff->tail = 0;
    buff->capacity = capacity;
    buff->size = 0;

    return buff;
}


bool cb_push(CircularBuffer* cb, int item) {
    // check if it is full
    if (cb_is_full(cb)) {
        fprintf(stderr, "The buffer is full!\n");
        return false;
    }

    pthread_mutex_lock(&cb->mutex);
    // wait while buffer is full
    while (cb->size == cb->capacity) {
        // in case the thread arrives here but the buffer is full then
        // it waits until other thread start consuming and pop an element
        // at that moment the other thread will trigger the condition not_full
        // and this thread will resume the execution and continue running
        // take into account that this function releases the mutex!! so other thread
        // can continue its execution!!!
        pthread_cond_wait(&cb->not_full, &cb->mutex);
    }

    cb->buffer[cb->tail] = item;
    cb->tail = (cb->tail + 1) % cb->capacity;
    cb->size++;

    pthread_cond_signal(&cb->not_empty);
    pthread_mutex_unlock(&cb->mutex);

    return true;
}


bool cb_pop(CircularBuffer* cb, int* value) {
    // check if buffer is empty
    if (cb_is_empty(cb)) {
        fprintf(stderr, "The buffer is empty!\n");
        return false;
    }

    pthread_mutex_lock(&cb->mutex);

    // wait while buffer is empty
    while (cb->size == 0) {
        // if the buffer is empty wait here until the condition of
        // the buffer not_empty is triggered by other thread that is pushing 
        // data to the buffer. In this case this thread resumes its execution
        pthread_cond_wait(&cb->not_empty, &cb->mutex);
    }

    *value = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % cb->capacity;
    cb->size--;

    // signals other threads that now the buffer is not full because it has poped
    // up some elements of the buffer
    pthread_cond_signal(&cb->not_full);
    pthread_mutex_unlock(&cb->mutex);

    return true;
}


bool cb_is_empty(const CircularBuffer* cb) {
    pthread_mutex_lock(&cb->mutex);
    bool result = (cb->size == 0);
    pthread_mutex_unlock(&cb->mutex);
    return result;
}


bool cb_is_full(const CircularBuffer* cb) {
    pthread_mutex_lock(&cb->mutex);
    bool result = (cb->size == cb->capacity);
    pthread_mutex_unlock(&cb->mutex);
    return result;
}

void cb_free(CircularBuffer* cb) {
    // destory sync primitives
    pthread_mutex_destroy(&cb->mutex);
    pthread_cond_destroy(&cb->not_full);
    pthread_cond_destroy(&cb->not_empty);

    // free resources
    free(cb->buffer);
    free(cb);
    cb = NULL;
}


// test the implementation
int main() {
    CircularBuffer* cb = cb_init(3);
    int value;

    // test 1
    assert(cb_is_empty(cb));
    assert(!cb_is_full(cb));

    // test 2
    assert(cb_push(cb, 10) == true);
    assert(cb_push(cb, 20) == true);
    assert(cb_push(cb, 30) == true);
    assert(cb_push(cb, 40) == false); // should fail (full)

    assert(cb_is_full(cb));

    // // test 3
    assert(cb_pop(cb, &value) == true);
    assert(cb_pop(cb, &value) == true);

    // // test 4: wrap around
    assert(cb_push(cb, 40) == true);
    assert(cb_push(cb, 50) == true);
    assert(cb_pop(cb, &value) == true);
    assert(cb_pop(cb, &value) == true);
    assert(cb_pop(cb, &value) == true);
    assert(cb_is_empty(cb));

    // // test 5: pop from empty buffer
    printf("The following error message is expected:\n");
    assert(cb_pop(cb, &value) == false);

    cb_free(cb);
    printf("All tests passed!\n");

    return 0;
}

