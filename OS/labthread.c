#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int num;
void *CalculateAverage(void *param); 
void *CalculateMinimum(void *param); 
void *CalculateMaximum(void *param); 



int main(int argc, int n,char *argv[])
{
	num=n;
	pthread_t tid1,tid2,tid3; 
	pthread_attr_t attr; 
	pthread_attr_init(&attr);
	
	char str[5];
	int arr[n];
	for(int i=0;i<n;i++)
		arr[i]=atoi(argv[i+1]);
	
	pthread_create(&tid1,&attr,CalculateAverage,&arr[0]);
	pthread_create(&tid2,&attr,CalculateMinimum,&arr[0]);
	pthread_create(&tid3,&attr,CalculateMaximum,&arr[0]);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	
	
}
void *CalculateAverage(void *param) {
	int avg=0;
	for(int i=0;i<num;i++)
		avg+=param[i];
	printf("Avergae = %f\n",(float)avg/num);
	pthread_exit(0);
}
void *CalculateMaximum(void *param) {
	int max=-58754;
	for(int i=0;i<num;i++)
	     if(param[i]>max)
	         max=param[i];
	printf("Maximum = %d\n",max);
	pthread_exit(0);
}
void *CalculateMinimum(void *param) {
	int min=584308;
	for(int i=0;i<num;i++)
		if(param[i]<min)
			min=param[i];
	printf("Minimum = %d\n",min);
	pthread_exit(0);
}
