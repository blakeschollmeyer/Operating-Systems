// Blake Schollmeyer
// prog4.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/* this data is shared by the thread(s) */
	struct p{
		int points_total;
		int points_inside;
	} shared_data;

/* the thread */
	void *runner(void *);

int main(int argc, char **argv)
{
/* the thread identifier */
	pthread_t tid;

/* set of attributes for the thread */
	pthread_attr_t attr;

/* declare shared data */
    struct p *shared_memory = &shared_data;
	shared_memory->points_inside = 0;
	shared_memory->points_total = 0;

/* get the default attributes */
	pthread_attr_init(&attr);

/* create the thread */
	pthread_create(&tid, &attr, runner, (void *)shared_memory);

/* now wait for the thread to exit */
	pthread_join(tid, NULL);

/* output the result to screen */
	double pi;
	pi = 4 * shared_memory->points_inside / (double)shared_memory->points_total;
	printf("Pi: %f\n", pi);
}

/**
 * The thread will begin control in this function
 */
void *runner(void *param)
{
	struct p * shared_data = (struct p*) param;
	
	/* Intializes random number generator */	
	time_t t;
	srand((unsigned) time(&t));	
	
	int i;
	for (i = 0; i < 10000000; i++){
		double x = (rand() / (double) (RAND_MAX)) * 2 - 1;
		double y = (rand() / (double) (RAND_MAX)) * 2 - 1;
		shared_data->points_total++;
		if ((x * x) + (y * y) < 1){
			shared_data->points_inside++;
		}
	}
	pthread_exit(0);
}
