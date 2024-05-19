#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>

// Number of slices in each pizza
#define S 8

// Shared resources
int num_slices = 0;
sem_t pizza;       // Number of available pizza slices
sem_t deliver;     // Semaphore to order new pizza
pthread_mutex_t mutex;  // Protects access to num_slices

void* student_thread(void* arg) {
         // Try to pick up a piece of pizza
        
	while(1){	
	pthread_mutex_lock(&mutex);
	
	while(num_slices==0){
		//pthread_mutex_unlock(&mutex);
		sem_post(&deliver);
            	sleep(5);
		sem_wait(&pizza); // Wait for the new pizza to arrive
            	//pthread_mutex_lock(&mutex);
            	num_slices--;
            	printf("Student %ld: Eating a slice of pizza. Slices left: %d\n", (long)arg, num_slices);
            	pthread_mutex_unlock(&mutex);
            	
	}
	       		
            //pthread_mutex_lock(&mutex);
            num_slices--;
            printf("Student %ld: Eating a slice of pizza. Slices left: %d\n", (long)arg, num_slices);
            pthread_mutex_unlock(&mutex);
            sleep(1); 
       }
       return NULL;
    
}

void* delivery_thread(void* arg) {
    
        
	while(1){
	sem_wait(&deliver);
        // Prepare a new pizza
        printf("Delivery person: Preparing a new pizza...\n");
        sleep(2); // Simulate time taken to prepare the pizza
        //pthread_mutex_lock(&mutex);
        num_slices = S;
        printf("Delivery person: New pizza delivered with %d slices.\n", num_slices);

        // Make slices available
        for (int i = 0; i < S; i++) {
            sem_post(&pizza);
        }
       } //pthread_mutex_unlock(&mutex);
    
}

int main() {
    // Initialize semaphores and mutex
    sem_init(&pizza, 0, 0);
    sem_init(&deliver, 0, 0);
    pthread_mutex_init(&mutex, NULL);

   
    int num_students = 12;
    pthread_t students[num_students];
    
    for (long i = 0; i < num_students; i++) {
        pthread_create(&students[i], NULL, student_thread, (void*)i);
    }
	pthread_t delivery1,delivery2,delivery3;
    pthread_create(&delivery1, NULL, delivery_thread, NULL);
    pthread_create(&delivery2, NULL, delivery_thread, NULL);
    //pthread_create(&delivery3, NULL, delivery_thread, NULL);
    
    for (int i = 0; i < num_students; i++) {
        pthread_join(students[i], NULL);
    }
    pthread_join(delivery1, NULL);
    pthread_join(delivery2, NULL);
    //pthread_join(delivery3, NULL);
    
    sem_destroy(&pizza);
    sem_destroy(&deliver);
    pthread_mutex_destroy(&mutex);

    return 0;
}

