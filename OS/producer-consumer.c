#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 
#include <stdbool.h>
#include <time.h>

#define BUFFER_SIZE 10


pthread_mutex_t mutex;
sem_t empty;
sem_t full;
	
int buffer_index = 0;

typedef int buffer_item;
buffer_item buffer[BUFFER_SIZE];

int insert_item(buffer_item item){
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	
    	if (buffer_index < BUFFER_SIZE){
       		buffer[buffer_index] = item;
       		buffer_index++;
        	pthread_mutex_unlock(&mutex);
       		sem_post(&full);
        	return 0;
    	} 
    	else{
        	pthread_mutex_unlock(&mutex);
        	sem_post(&empty);
        	return -1; 
    	}
}

int remove_item(buffer_item *item){
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	if(buffer_index>-1){
		*item = buffer[--buffer_index];
       		 pthread_mutex_unlock(&mutex);
        	 sem_post(&empty);
        	 return 0;
	}
	else{
		pthread_mutex_unlock(&mutex);
        	sem_post(&full);
        	return -1; 
	}
}

void *producer(void *param){
	buffer_item item;
	while(true){
		sleep(1);
		//srand(time(NULL));
		item=rand()%100;
		if(insert_item(item))
			fprintf(stderr,"Report error condition");
		else
			printf("Producer produced %d\n",item);
	}
	pthread_exit(0);
}
void *consumer(void *param){
	buffer_item item;
	while(true){
		sleep(1);
		if(remove_item(&item))
			fprintf(stderr,"Report error condition");
		else
			printf("Consumer consumed %d\n",item);
	}
	pthread_exit(0);
}
int main(){
	int num=10;
	pthread_t tid[num]; 
	pthread_attr_t attr; 
	
	pthread_mutex_init (&mutex,NULL);
	
	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);
	
	pthread_attr_init(&attr);
	
	for(int i=0;i<num;i+=2)
		pthread_create(&tid[i],&attr,producer,"hello");
	for(int i=1;i<num;i+=2)	
		pthread_create(&tid[i+1],&attr,consumer,"hello");
	
	for(int i=0;i<num;i+=2){
		pthread_join(tid[i], NULL);
   		pthread_join(tid[i+1], NULL);
   	}	
}
