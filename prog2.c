// Blake Schollmeyer

// Using the Collatz conjecture algorithm, when the conjecture algorithm is
// continually applied, all positive integers will eventually reach one.
// The fork() sys call generates this sequence in the child process. Provide a
// starting number in the command line to run the program correctly.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define MAX_SEQUENCE 50

typedef struct {
	int size;
	int num[MAX_SEQUENCE];
} shared_data;

int main(int argc, char *argv[])
{
	const char *name = "OS";
	int shm_fd;
	int i;
	shared_data* shared_memory;
	int pid;

	shm_fd = shm_open(name, O_CREAT|O_RDWR, 0666);

	ftruncate(shm_fd, sizeof(shared_data));

	shared_memory = (shared_data *) mmap(0, sizeof(shared_data), PROT_WRITE, MAP_SHARED, shm_fd, 0);

	if((pid = fork()) == -1)
	{
		perror("Failed to create child process");
		return 1;
	}

	if(pid > 0)
	{
		wait(NULL);
		for(i = 0; i < shared_memory->size + 1; i++)
		{
			printf("%d ", shared_memory->num[i]);
			if(i == shared_memory->size)
			{
				printf("\n");
			}
		}
	}

	else if(pid == 0)
	{
		shared_memory->num[0] = atoi(argv[1]);

		if(atoi(argv[1]) == 1)
		{
			exit(0);
		}

		if(atoi(argv[1]) < 1)
		{
			exit(0);
		}

		for(i = 1; i < MAX_SEQUENCE; i++)
		{
			if(shared_memory->num[i - 1] % 2 == 0)
			{
				shared_memory->num[i] = shared_memory->num[i - 1] / 2;
			}
			else
			{
				shared_memory->num[i] = (shared_memory->num[i - 1] * 3) + 1;
			}

			if(shared_memory->num[i] == 1)
			{
				shared_memory->size = i;
				break;
			}
		}
		exit(0);
	}

	shm_unlink(name);
	return 0;
}
