#define StudyTutoringChairs 3
#define MAX_Wait 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 
#include <semaphore.h> 

//Semiphore to protect the students
sem_t StudentSemiphore;

//Lock to keep the TA from being accessed by more than one student
sem_t TASem;

//General Mutex lock to protect variables and values. 
pthread_mutex_t mutex;

//Chairs that are available for students to sit in with TA
int numOfChairs[1];

//Counter variables for general useage
int count = 0;

//Used to determine which seat is availbale for the students
int NextSeat = 0;

//Keepts track of next student in line to stop stuying by
//themselfs and to get a seat.
int NextStud = 0;


//Method Prototypes
void waiting(void);
void* studentLife(void* stu_id);
void* TATeach();


//Main method which will create student Threads, will also 
//create TA thread 
int main(int argc, char **argv){
	//Declare Id Variable
	int* ID;
	
	//decleare the thread pointers
	pthread_t *students;
	pthread_t ta;
	
	//The number of students that going to TA hours
	int  numOfStudents = 4 ;
	
	//Create Id for 
	ID = (int*)malloc(sizeof(int) * numOfStudents);
	
	//Stupid counter variable because c won't let me make it in the loop
	int x;

	printf("ZZZZZZZZ... shhhhh the TA is sleeping...ZZZZZZZZZ\n");
	//initialize
	students = (pthread_t*)malloc(sizeof(pthread_t) * numOfStudents);
	
	
	memset(ID, 0, numOfStudents);
	sem_init(&StudentSemiphore,0,0);
	sem_init(&TASem,0,1);
	srand(time(NULL));
	pthread_mutex_init(&mutex,NULL);
	
	
	for(x=0; x<numOfStudents; x++)
	{
		pthread_create(&ta,NULL,TATeach,NULL);
		ID[x] = x+1;
		pthread_create(&students[x], NULL, studentLife, (void*) &ID[x]);
	} 
	
	pthread_join(ta, NULL);
	
	for(x=0; x<numOfStudents;x++)
	{
		pthread_join(students[x],NULL);
	}	
	
	printf("No students left, TA has gone back to sleep.");
	return 0;
}

//Generates Random sleep time to the set max value
void waiting(void)
{
	int time = rand() % MAX_Wait + 1;sleep(time);
}



//Thread for the Student Programming
void* studentLife(void* stu_id)
{
	int studName = *(int*)stu_id;

	//Start All student out by working alone
	printf("%d arived.\n",studName);		
	
	while(1)
	{
		waiting();
		pthread_mutex_lock(&mutex);
		if(count < StudyTutoringChairs)	
		{
			numOfChairs[NextSeat] = studName;
			
			count++;
			printf("%d takes a chair\n",studName);
			NextSeat = (NextSeat+1) % StudyTutoringChairs;
			
			printf("SelfStudying\n");
			
			pthread_mutex_unlock(&mutex);
			sem_post(&StudentSemiphore);
			sem_wait(&TASem);
			printf("%d is done getting help and leaves");
			return 0;
		}
		else
		{
			pthread_mutex_unlock(&mutex);
			printf("No seats Available for Student %d, They have to work alone\n",studName);
		}
	}
	printf("%d is done getting help and leaves");
				
}

//TA Teaching
void* TATeach()
{
	while(1)
	{
		sem_wait(&TASem);	
		
		//Lock the mutex lock so other threads cannot access the TA
		pthread_mutex_lock(&mutex);
		
		printf("TA is helping %d\n",numOfChairs[NextStud] + 1);
			
		numOfChairs[NextStud]=0;
		count--;
		
		sleep(2);
		printf("All Three chairs are filled with students waiting for the TA\n");
		NextStud = (NextStud + 1) % StudyTutoringChairs;
		waiting();	
		
		//unlock the mutex lock
		pthread_mutex_unlock(&mutex);
		sem_post(&TASem);
		
		return 0;
	}	
}
