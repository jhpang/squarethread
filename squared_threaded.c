#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define NUMBER_OF_THREADS 8
#define START_NUMBER 1
#define END_NUMBER 10000

/*
Answer the following question as a comment in your code:
Is the multi-threaded version of this program faster or slower?
Explain why it's faster or slower.

The multithreaded version of this program is slower because the program
essentially takes a simple caluclation, not anything too complex.
Having a linear system that does the operation in this case would be more beneficial.
Since threads do not actually speed up the execution of code, having multiple threads run
and having each thread run one simple squaring operation, a single threaded process could have gotten
those squaring operations done by the time the multi threads were made. 
I think in this case, the program specifically, the cost of launching the threads didnt benefit
the task and that's why the single threaded application was faster.
*/

FILE *f;

void *square_op(void *tid)
{
  int sq = (long) tid;
  fprintf(f, "%lu squared = %lu\n", (long) tid, sq*sq);
  pthread_exit(NULL);
}

int main() {
  // START: Do not modify anything here
  struct timeval start_time, end_time;
  gettimeofday(&start_time, 0);
  long unsigned i;
  f = fopen("./squared_numbers.txt", "w");
  // END: Do not modify anything here

  /*for (i=START_NUMBER; i<=END_NUMBER; i++) {
    fprintf(f, "%lu squared = %lu\n", i, i*i);
  }*/

  pthread_t threads[NUMBER_OF_THREADS];
  long status;
  long num = START_NUMBER;
  for (i=START_NUMBER; i<=NUMBER_OF_THREADS + 1; i++)
  {

    if (num > END_NUMBER)
    {
      printf("Done!\n");
      break;
    }
    else if (i > NUMBER_OF_THREADS) { i = 0; }
    else
    {
      status = pthread_create(&threads[i], NULL, square_op, (void *)num);
      num++;
    }
  }
  if (status != 0)
  {
    printf("Oops. pthread_create returned error code %0d\n", status);
    exit(-1);
  }
  /* Wait for all threads to finish, before exiting process */
  for (i=START_NUMBER; i<NUMBER_OF_THREADS; i++)
  {
    if (pthread_join(threads[i], NULL))
    { printf("Thread %0d failed to join\n"); }
  }


  // START: Do not modify anything here
  fclose(f);
  gettimeofday(&end_time, 0);
  float elapsed = (end_time.tv_sec-start_time.tv_sec) * 1000.0f + \
                  (end_time.tv_usec-start_time.tv_usec) /1000.0f;
  printf("took %0.2f milliseconds\n", elapsed);
  // END: Do not modify anything here

}
