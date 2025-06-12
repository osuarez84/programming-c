#include "circular_buffer.h"
#include <pthread.h>
#include <unistd.h>

#define ITEMS_PERPRODUCER 1000
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3
#define BUFFER_SIZE 10


CircularBuffer* cb;


void* producer(void* arg) {
    int thread_id = *(int*)arg;

    // just compute some randome init and end values for pushing into the buffer
    int start = thread_id * ITEMS_PERPRODUCER;
    int end = start + ITEMS_PERPRODUCER;
    
    printf("Producer %d: Producing %d to %d\n", thread_id, start, end);

    for (int i = start; i < ITEMS_PERPRODUCER; i++) {
        while (!cb_push(cb, i)) {
            printf("Producer %d: buffer full, retrying...\n", thread_id);
        }
        usleep(1000 * (rand() % 3));
    }

    printf("Producer %d: Done\n", thread_id);

    return NULL;
}

void* consumer(void* arg) {
    int thread_id = *(int*)arg;
    int count = 0;
    int value;

    printf("Consumer %d: starting\n", thread_id);

    while (count < ITEMS_PERPRODUCER) {
        if (cb_pop(cb, &value)) {
            printf("Consumer %d consumed the value %d\n", thread_id, value);
            count++;
        } else {
            printf("Consumer %d: buffer empty, waiting...\n", thread_id);
            usleep(1000);
        }
    }

    printf("Consumer %d: consumed %d items\n", thread_id, count);
    return NULL;
}


int main() {
     cb = cb_init(BUFFER_SIZE);
    if (cb == NULL) {
        fprintf(stderr, "Can not initialized the buffer!\n");
        return 1;
    }

    pthread_t producers[NUM_PRODUCERS]; // prepare an array of producers
    pthread_t consumers[NUM_CONSUMERS]; // prepare an array of consumers
    int consumer_ids[NUM_CONSUMERS];
    int producer_ids[NUM_PRODUCERS];
    
    printf("Starting test with %d producers and %d consumers\n", NUM_PRODUCERS, NUM_CONSUMERS);


    // create producer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        if(pthread_create(&producers[i], NULL, producer, &producer_ids[i]) != 0) {
            fprintf(stderr, "Failed to create producer thread");
            return 1;    
        }
    }


    // create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        if(pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]) != 0) {
            fprintf(stderr, "Failed to create consumer thread");
            return 1;
        }
    }

    // wait for all producers to finish
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    // wait for all consumers to finish
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    cb_free(cb);
    return 0;
}