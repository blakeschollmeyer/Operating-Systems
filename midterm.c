// Blake Schollmeyer
// MIDTERM Corrections
// Must complile with -lrt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define MAX_SIZE 30

typedef struct 
{
	int data[MAX_SIZE];
	int upper_low;  
} shared_data; 

int main(int argc, char *argv[])
{	
   int number; 

   if (argc == 2)
   {
      number = atoi(argv[1]); 
   }
   else
   {
      printf("ERROR\n"); 
      exit(1); 
   }
	
   const char *name = "BlakeSchollmeyer";

   int shm_fd; 
	
   shared_data  *shared_memory;
	
   shm_fd = shm_open(name, O_CREAT|O_RDWR, 0666);

   ftruncate(shm_fd, sizeof(shared_data)); 

   shared_memory = (shared_data *) mmap(0, sizeof(shared_data), PROT_WRITE, MAP_SHARED, shm_fd, 0); 

   if (number > 0 && number <= MAX_SIZE)
   {
      shared_memory->upper_low = number;
   }
   else
   {
      printf("Error in command line.");
      exit(1);
   }

   int pid1 = 5; 
   int pid2 = 5; 

   pid1 = fork(); 
	
   if (pid1 == -1)
   {
      perror("Failed to create child process"); 
      return 1; 
   }
	
   if (pid1 > 0)
   {
      wait(NULL); 

      int i; 
      for (i = 0; i < MAX_SIZE; i++)
      {
         printf("%d ", shared_memory->data[i]); 
      }
   }
   else if (pid1 == 0)
   {
      pid2 = fork(); 

      if (pid2 == 0)
      {
         int i; 
         for (i = 0; i < shared_memory->upper_low; i++)
         {
            shared_memory->data[i] = pid1; 
	 }
      }
      else
      {
         int i; 
	 for (i = shared_memory->upper_low; i < MAX_SIZE; i++)
	 {
	    shared_memory->data[i] = pid2; 
	 }
      }
   }
	
   shm_unlink(name); 
   return 0; 
}
