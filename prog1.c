#define MAX_SIZE1 20
#define MAX_SIZE2 10
#define MILLION 1000000L
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

void function_to_time()
{
   int i;
   sleep(2);
   for(i = 0; i < 100000000; i++);
}

typedef struct {
   char name[MAX_SIZE1];
   int score[MAX_SIZE2];
} students_t;

int mycmp(const void *pa, const void *pb)
{
   students_t *a = (students_t *) pa;
   students_t *b = (students_t *) pb;
   int i, sum1 = 0, sum2 = 0;

   for(i = 0; i < 10; i++)
   {
      sum1 += a->score[i];
      sum2 += b->score[i];
   }
   return (sum2 - sum1);	
}

int main(int argc, char *argv[])
{
   long timedif;
   struct timespec tpend, tpstart;

   srand(time(NULL));
   students_t* ptr;
   int i, j;

   char *names[] = {"Blake", "Clayton", "Kyrsten", "Irwin", "Chelle", "Meriel", "Miranda", "Grenville", "Florrie", "Tommy", "Doris", "Saranna", "Marilynn", "Rebeccah", "Geena", "Mellony", "Mariabella", "Kalie", "Caris", "Charlton", "Walker", "Jannette", "Ansel", "Xavior", "Danielle", "Maureen", "Elenora", "Anne", "Clay", "Jaylin"}; 

   ptr = (students_t *)malloc(sizeof(students_t) * atoi(argv[1]));
   students_t *p = ptr;
   for(i = 0; i < atoi(argv[1]); i++)
   {
      strcpy(p->name, names[i]);
      for(j = 0; j < 10; j++)
      {
         p->score[j] = (rand() % 51) + 50;
      }
      p++;
   }

   qsort(ptr, atoi(argv[1]), sizeof(students_t), mycmp);
   p = ptr;
   int sum = 0;

   for(i = 0; i < atoi(argv[1]); i++)
   {
      printf("%s\n", p->name);
      for(j = 0; j < 10; j++)
      {
         sum += p->score[j];
	 printf("%d ", p->score[j]);

         if(j == 9)
         {
            printf("Total is: %d", sum);
	    sum = 0;
	 }
      }
      printf("\n");
      p++;
   }
 
   free(ptr);
   function_to_time();
   timedif = MILLION * (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_nsec - tpstart.tv_nsec) / 1000;
   printf("The function_to_time took %ld microseconds to execute.\n", timedif);
   return 0;}
