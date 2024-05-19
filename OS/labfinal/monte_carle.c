#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
int countInCircle=0,countTotal=1;
void *runner(void *param);

int main(int argc, char *argv[]){
	int num=atoi(argv[1]);

	pthread_t tid[num]; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */
	pthread_attr_init(&attr);
		
	for(int i=0;i<num;i++){
		pthread_create(&tid[i],&attr,runner,"1000");
		pthread_join(tid[i],NULL);
	}
	
	float pie= 4*((float)countInCircle/countTotal);
	printf("Ratio = %f\n",pie);
}

float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; 
    return min + scale * ( max - min );      
}

void *runner(void *param) {
	srand((unsigned int)time(NULL));
	float x,y ;
	double distance;
	int n=atoi(param);
	
	for (int i=0;i<n;i++){
		x=float_rand(-1,1);
		y=float_rand(-1,1);
		distance=sqrt((double)((x-0)*(x-0))+((y-0)*(y-0)));
		
		if(distance<=1.00)
			countInCircle++;
		countTotal++;	
		
	}

	pthread_exit(0);
}

