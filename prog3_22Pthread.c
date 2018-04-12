//Blake Schollmeyer
//prog3_22Pthread

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_SEQUENCE 100

/* this data is shared by the thread(s) */
	struct p{
		long num[MAX_SEQUENCE];
		int size;
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

/* check for the existence and validity of the user input */
	if (argc != 2) {
		// display error message
		printf("Incorrect number of parameters!\n");
		// exit
		return(-1);
	}
	if (atoi(argv[1]) <= 0){ 
		printf("Incorrect argument!\nA positive integer is required.\n"); 
		return(-2); 
	}
/* store the initial value before calling the thread */
	shared_memory->size = atoi(argv[1]);

/* get the default attributes */
	pthread_attr_init(&attr);

/* create the thread */
	pthread_create(&tid, &attr, runner, (void *)shared_memory);

/* now wait for the thread to exit */
	pthread_join(tid, NULL);

/* output the result to screen */
	int i;
	for(i = 0; i < shared_data.size - 1; i++)
		printf("%ld,",shared_data.num[i]);
	printf("%d\n",shared_data.num[shared_data.size - 1]);	
	return 0;
}

/**
 * The thread will begin control in this function
 */
void *runner(void *param)
{
	struct p * shared_data = (struct p*) param;
    int n = shared_data->size;
	int i = 0;

	do {
		shared_data->num[i] = n;
		if ((n%2) == 0){
			n/=2;
		}
		else {
			n = 3 * n + 1;
		}		
		i++;
		
	} while((shared_data->num[i-1]) != 1);
	shared_data->size = i;
	pthread_exit(0);
}
