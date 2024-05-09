#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // for sleep
#define BUFFER_SIZE 5

typedef int buffer_item;
buffer_item buffer[BUFFER_SIZE];
int buffer_index = 0;

pthread_mutex_t mutex;
sem_t empty, full;

int insert_item(buffer_item item) {
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    if (buffer_index < BUFFER_SIZE) {
        buffer[buffer_index] = item;
        buffer_index++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        return 0; // Success
    } else {
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        return -1; // Buffer full
    }
}

int remove_item(buffer_item *item) {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    if (buffer_index > 0) {
        *item = buffer[--buffer_index];
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        return 0; // Success
    } else {
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        return -1; // Buffer empty
    }
}

void *producer(void *param) {
    buffer_item item;
    while (1) {
        sleep(1);
        item = rand()%100; // Generate random item
        if (insert_item(item))
            fprintf(stderr, "Report error condition\n");
        else
            printf("Producer produced %d\n", item);
    }
    pthread_exit(0);
}

void *consumer(void *param) {
    buffer_item item;
    while (1) {
        sleep(1);
        if (remove_item(&item))
            fprintf(stderr, "Report error condition\n");
        else
            printf("Consumer consumed %d\n", item);
    }
    pthread_exit(0);
}

int main() {
    int num = 10;
    pthread_t tid[num];
    pthread_attr_t attr;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0); // Initialize full semaphore to 0
    pthread_attr_init(&attr);

    for (int i = 0; i < 5; i ++) {
        pthread_create(&tid[i], &attr, producer, NULL);
    }
    for (int i = 5; i < num; i ++) {
        pthread_create(&tid[i], &attr, consumer, NULL);
    }
    for (int i = 0; i < num; i++)
        pthread_join(tid[i], NULL);

    // Cleanup
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);


    pthread_exit(0);
}

