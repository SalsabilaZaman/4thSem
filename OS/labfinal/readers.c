#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 
#include <stdbool.h>
#include <time.h>

pthread_mutex_t r_mutex;
pthread_mutex_t rw_mutex;
int readcount=0;
int writerId = 1;

void *readers(void* param){
	pthread_mutex_lock(&r_mutex);
	
	readcount ++;
	if(readcount==1)
		pthread_mutex_lock(&rw_mutex);	
	pthread_mutex_unlock(&r_mutex);
	
	printf("Reader-%ld is reading\n",(long)param);
	
	pthread_mutex_lock(&r_mutex);
	readcount --;
	printf("Reader-%ld is leaving\n",(long)param);
	if(readcount==0){
		//printf("No reader is reading now\n");	
		pthread_mutex_unlock(&rw_mutex);
	}
	pthread_mutex_unlock(&r_mutex);
			
	pthread_exit(0);
}
void *writers(void* param){
	pthread_mutex_lock(&rw_mutex);
	
	printf("Writer-%ld is writing\n",(long)param);
	
	pthread_mutex_unlock(&rw_mutex);
	pthread_exit(0);
}

int main(){
	int num=10;
	pthread_t tid[num]; 
	pthread_attr_t attr; 
	
	pthread_mutex_init (&r_mutex,NULL);
	pthread_mutex_init (&rw_mutex,NULL);
	
	
	pthread_attr_init(&attr);
	
	for(long i=0;i<num;i+=2){
		pthread_create(&tid[i],&attr,readers,(void*)i);	
		pthread_create(&tid[i+1],&attr,writers,(void*)i);
	}
	for(long i=0;i<num;i+=2){
		pthread_join(tid[i], NULL);
   		pthread_join(tid[i+1], NULL);
   	}
   	
   	pthread_mutex_destroy(&r_mutex);
    	pthread_mutex_destroy(&rw_mutex);
    	
    	return 0;	
}
