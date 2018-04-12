// Blake Schollmeyer
// prog4_21.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_SEQUENCE 100

/* this data is shared by the thread(s) */
	struct p{
		long nums[MAX_SEQUENCE];
		int size;
		double average;
		long max;
		long min;
	} shared_data;

/* the threads */
	void *runner_avg(void *);	
	void *runner_max(void *);	
	void *runner_min(void *);

int main(int argc, char **argv)
{
/* the thread identifier */
	pthread_t tid[3];

/* set of attributes for the thread */
	pthread_attr_t attr;

/* declare shared data */
    struct p *shared_memory = &shared_data;

/* check for the existence and validity of the user input */
	if (argc <= 2) {
		// display error message
		printf("Incorrect number of parameters!\n");
		// exit
		return(-1);
	}
	
/* store the input values before calling the thread */
	int i;
	for (i = 1; i < argc; i++){
		shared_memory->nums[i-1] = atoi(argv[i]);
	}
/* set the size to the number of values input */
	shared_memory->size = argc - 1;
	

/* get the default attributes */
	pthread_attr_init(&attr);

/* create the threads */
	pthread_create(&tid[0], &attr, runner_avg, (void *)shared_memory);
	pthread_create(&tid[1], &attr, runner_max, (void *)shared_memory);
	pthread_create(&tid[2], &attr, runner_min, (void *)shared_memory);

/* now wait for the threads to exit */
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);

/* output the result to screen */
	printf("Average: %f\n", shared_memory->average);
	printf("Maximum: %ld\n", shared_memory->max);
	printf("Minimum: %ld\n", shared_memory->min);
}
/**
 * The threads will begin control in this function
 */
void *runner_avg(void *param)
{
	struct p * shared_data = (struct p*) param;
	int i;
	double sum = 0;
	for (i = 0; i < shared_data->size; i++){
		sum += shared_data->nums[i];
	}
	shared_data->average = sum / i;
	pthread_exit(0);
}

void *runner_max(void *param)
{
	struct p * shared_data = (struct p*) param;
	int i;
	long max = shared_data->nums[0];
	for (i = 1; i < shared_data->size; i++){
		if (max < shared_data->nums[i]){
			max = shared_data->nums[i];
		}
	}
	shared_data->max = max;
	pthread_exit(0);
}

void *runner_min(void *param)
{
	struct p * shared_data = (struct p*) param;
	int i;
	long min = shared_data->nums[0];
	for (i = 1; i < shared_data->size; i++){
		if (min > shared_data->nums[i]){
			min = shared_data->nums[i];
		}
	}
	shared_data->min = min;
	pthread_exit(0);
}
