#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int *Buffer, *producer_count, *consumer_count;
int N, p, c;
int in, out;

sem_t mutex;        //semaphore for mutual exclusion
sem_t empty_cnt;    //'empty_cnt' semaphore which tracks number of empty entries in buffer
sem_t full_cnt;     //'full_cnt' semaphore which tracks number of occupied entries in buffer


void *
producer (void *p_ID)
{
  int producer_Id = *(int *) p_ID;
  producer_count[producer_Id] = 0;
  printf ("Producer # %d is producing\n", producer_Id);
  while (producer_count[producer_Id] < 10 * N)  //Each producer produces 10*N items.
    {
 
      sem_wait (&empty_cnt);
      sem_wait (&mutex);
      //Critical Section entered
      Buffer[in] = producer_Id;
      in = (in + 1) % N;
      producer_count[producer_Id]++;
      //Critical Section exited
      sem_post (&mutex);
      sem_post (&full_cnt);

    }
  return NULL;
}

void *
consumer (void *c_ID)
{
  int consumer_Id = *(int *) c_ID;
  consumer_count[consumer_Id] = 0;
  printf ("Consumer # %d is consuming\n", consumer_Id);
  while (1)
    {
      sem_wait (&full_cnt);
      sem_wait (&mutex);
      //Critical Section entered
      Buffer[out] = consumer_Id;
      out = (out + 1) % N;
      consumer_count[consumer_Id]++;
      //Critical Section exited
      sem_post (&mutex);
      sem_post (&empty_cnt);
    }
  return NULL;
}

int
main (int argc, char *argv[])
{
  int i, P_total = 0, C_total = 0, val;
  if (argc > 1)
    {
      p = atoi (argv[1]);
      c = atoi (argv[2]);
      N = atoi (argv[3]);
    }
  else
    {
      printf ("Please enter the command line arguments correctly\n");
      return 0;
    }
  Buffer = (int *) malloc (N * sizeof (int));
  producer_count = (int *) malloc (p * sizeof (int)); // Keeps count of items produced by each producer thread
  consumer_count = (int *) malloc (c * sizeof (int)); // Keeps count of items consumed by each consumer thread
  //Initializing the semaphores:

  sem_init (&mutex, 0, 1);
  sem_init (&empty_cnt, 0, N);
  sem_init (&full_cnt, 0, 0);

  //Creating arrays of producer and consumer threads :
  pthread_t producer_thread[p];
  pthread_t consumer_thread[c];
  int p_ID[p], c_ID[c];   // Arrays to store the thread id's of each thread.

  for (i = 0; i < p; ++i)
    {
      p_ID[i] = i;
      pthread_create (&producer_thread[i], NULL, producer, (void *) &p_ID[i]);
    }
  for (i = 0; i < c; ++i)
    {
      c_ID[i] = i;
      pthread_create (&consumer_thread[i], NULL, consumer, (void *) &c_ID[i]);
    }

  for (i = 0; i < p; ++i)
    pthread_join (producer_thread[i], NULL);  //Pause execution of main thread and allow the producer threads to run.

  for (i = 0; i < p; ++i)
    P_total += producer_count[i];

  for (i = 0; i < c; ++i)
    C_total += consumer_count[i];

  sem_getvalue (&empty_cnt, &val);
  while (val < N);                        //We leave the main thread waiting till the buffer becomes empty.
  for (i = 0; i < c; ++i)
    pthread_cancel (consumer_thread[i]);  //Killing the consumer threads since all the producers are done producing and also the buffer is empty.

  printf ("Total number of items produced : %d\n", P_total);
  printf ("Total number of items consumed : %d\n", C_total);

  free(Buffer) ;
  free(producer_count) ;
  free(consumer_count) ;
  sem_destroy(&mutex) ;
  sem_destroy(&empty_cnt) ;
  sem_destroy(&full_cnt) ;
  
  return 0;
}
