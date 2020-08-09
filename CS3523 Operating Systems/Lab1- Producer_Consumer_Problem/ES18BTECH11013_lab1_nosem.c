#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int *Buffer, *producer_count, *consumer_count;
int N, p, c;
int buf_count, in, out;   //buf_count keeps track of the number elements in the buffer.

void *
producer (void *p_ID)
{
  int producer_Id = *(int *) p_ID;
  producer_count[producer_Id] = 0;
  printf ("Producer # %d is producing\n", producer_Id);
  while (producer_count[producer_Id] < 10 * N)  //Each producer writes produces 10*N items.
    {
      while (buf_count >= N);    //keep waiting if buffer is full.

      Buffer[in] = producer_Id;
      in = (in + 1) % N;
      buf_count++;
      producer_count[producer_Id]++;
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
      while (buf_count <= 0); // do nothing as buffer is empty

      Buffer[out] = consumer_Id;
      out = (out + 1) % N;
      buf_count--;
      consumer_count[consumer_Id]++;
    }
  return NULL;
}

int
main (int argc, char *argv[])
{
  int i, P_total = 0, C_total = 0;
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
  pthread_t producer_thread[p];
  pthread_t consumer_thread[c];
  int p_ID[p], c_ID[c];   // Store the thread id's of each thread.

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

  while (buf_count > 0);  //We leave the main thread waiting till buffer is empty.
  for (i = 0; i < c; ++i)
    pthread_cancel (consumer_thread[i]);  //Killing the consumer threads since all the producers are done producing and also the buffer is empty.

  printf ("Total number of items produced : %d\n", P_total);
  printf ("Total number of items consumed : %d\n", C_total);

  free(Buffer) ;
  free(producer_count) ;
  free(consumer_count) ;

  return 0;
}
