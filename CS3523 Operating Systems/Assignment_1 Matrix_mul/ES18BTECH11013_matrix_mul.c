/*
 * Program: Speedup calculation of matrix multiplication with
 *          multi-processing and multi-threading.
 * Author:  Nishant Reddy
 * Roll# :  ES18BTECH11013
 */

#include <stdlib.h>  /* for exit, atoi */
#include <stdio.h>   /* for fprintf */
#include <errno.h>   /* for error code eg. E2BIG */
#include <getopt.h>  /* for getopt */
#include <assert.h>  /* for assert */
#include <pthread.h>
#include <sys/time.h>
#include <sys/shm.h> 
#include <sys/wait.h> /* for wait() */ 
#include <unistd.h>   /* for fork() */
#define N 4


typedef struct pair
{
  int start ;
  int end ;
} pair;
pair threadInfo[N] ;

int *aPtr;
int *bPtr;
int *cPtr;
int cRows; 
int cCols;
int aRows; 
int aCols; 
int bRows; 
int bCols;
char interactive = 0;

/*
 * Show usage of the program
 */
void
usage (int argc,
       char *argv[])
{
  fprintf (stderr,
           "Usage:\n");
  fprintf (stderr,
           "%s --ar <rows_in_A>  --ac <cols_in_A>"
           " --br <rows_in_B>  --bc <cols_in_B>"
           " [--interactive]",
           argv[0]);
  exit(EXIT_FAILURE);
}

/*
 * Input a given 2D matrix
 */
void
input_matrix ()
{
  printf("Enter A:\n");
  fflush(stdout);
  for (int i = 0; i < aRows; i++)
    {
      for (int j = 0; j < aCols; j++)
              scanf("%d", aPtr+(i*aCols+j));     
    }

  fprintf(stdout,
          "Enter B:\n");
  fflush(stdout);
  for (int i=0; i< bRows; i++)
    {
      for (int j=0; j< bCols; j++)
              fscanf(stdin, "%d", bPtr+(i*bCols+j));     
    }
}

/*
 * Output a given 2D matrix
 */
void
output_matrix ()
{
  printf("Result:\n");
  fflush (stdout) ;
  for (int i = 0; i < aRows; i++)
    {
      for (int j = 0; j < bCols; j++)
              printf(/*stdout,*/ "%d ", *(cPtr+(i*bCols+j)));

      fprintf(stdout, "\n");
      fflush (stdout) ;
    }
}

/*
 * Allocating space on the Heap for each matrix
 */
void
create_matrix ()
{
  aPtr = (int *)malloc (aRows*aCols*sizeof(int));
  bPtr = (int *)malloc (bRows*bCols*sizeof(int));
  cPtr = (int *)malloc (aRows*bCols*sizeof(int)); 
}

void
free_matrix()
{
  free (aPtr);
  free (bPtr);
  free (cPtr);
}

/*
 * Initializing the matrix with pseudo-random numbers
 */
void
init_matrix ()
{
  srand(time(0)); 
  for (int i = 0; i < aRows; ++i)
    {
      for (int j = 0; j < aCols; ++j)
              *(aPtr+i*aCols+j) = rand () ;
    }
  for (int i = 0; i < bRows; ++i)
    {
      for (int j = 0; j < bCols; ++j)
              *(bPtr+i*bCols+j) = rand () ;
    }
}

void *
ThreadFunc (void *arg)
{

  for (int i = ((pair *)arg)->start; i < ((pair *)arg)-> end ; ++i)
    {
      for (int j = 0; j < bCols; ++j)
        {
          for (int k = 0; k < aCols; ++k)
                  *(cPtr+i*bCols+j) += (*(aPtr+i*aCols+k))* (*(bPtr+k*bCols+j)) ;  //C[i][j] += A[i][k]*B[k][j]
        }       
    }
  
  return NULL;
}

unsigned long long
single_thread_mm()
{
  create_matrix ();
  struct timeval start, end;
  double timeMicrosec ;
  if (interactive)
          input_matrix ();
  else
          init_matrix ();

  //start timer
  gettimeofday(&start, NULL);
  for (int i = 0; i < aRows; ++i)
    {
      for (int j = 0; j < bCols; ++j)
      {
        for (int k = 0; k < aCols; ++k)
                *(cPtr+i*bCols+j) += (*(aPtr+i*aCols+k))* (*(bPtr+k*bCols+j)) ;  //C[i][j] = A[i][k]*B[k][j]
      }
       
    }
  gettimeofday(&end, NULL);; 
  //end timer

  timeMicrosec = (end.tv_sec - start.tv_sec) * 1e6; 
  timeMicrosec = (timeMicrosec + (end.tv_usec-start.tv_usec));

  if(interactive)
       output_matrix();

  free_matrix ();

  return (unsigned long long)timeMicrosec ;
}

unsigned long long
multi_thread_mm()
{
  create_matrix ();
  if (interactive)
          input_matrix ();
  else
          init_matrix ();

  struct timeval start, end;
  pthread_t thread[N];
  double timeMicrosec ;
  int rem = aRows%N;
  threadInfo[0].end = aRows/N ;
  if(rem > 0)
    {
      threadInfo[0].end++ ;
      rem--;
    }

  for (int i = 1; i < N; ++i)
    {
      threadInfo[i].start = threadInfo[i-1].end;
      threadInfo[i].end = threadInfo[i].start + (aRows/N);
      if (rem > 0)
        {
          threadInfo[i].end +=1 ;
          rem-- ;
        }
    }
  
  //start timer
  gettimeofday(&start, NULL);
  for (int i = 0; i < N; ++i)
          pthread_create (&thread[i], NULL, ThreadFunc,(void *) &threadInfo[i]);

  for (int i = 0; i < N; ++i)
          pthread_join (thread[i], NULL);

  gettimeofday(&end, NULL);
  //end timer

  if (interactive)
        output_matrix ();

  timeMicrosec = (end.tv_sec - start.tv_sec) * 1e6; 
  timeMicrosec = (timeMicrosec + (end.tv_usec-start.tv_usec));
  free_matrix ();

  return (unsigned long long)timeMicrosec ;

}

unsigned long long
multi_process_mm()
{
  double timeMicrosec ;
  struct timeval start, end;
  int aId = shmget(IPC_PRIVATE, aRows*aCols*sizeof(int), IPC_CREAT | 0666);
  int bId = shmget(IPC_PRIVATE, bRows*bCols*sizeof(int), IPC_CREAT | 0666);
  int cId = shmget(IPC_PRIVATE, aRows*bCols*sizeof(int), IPC_CREAT | 0666);
  aPtr = (int*) shmat(aId, NULL, 0);
  bPtr = (int*) shmat(bId, NULL, 0);
  cPtr = (int*) shmat(cId, NULL, 0);

  if (interactive)
          input_matrix ();
  else
          init_matrix ();

  //start timer
  gettimeofday(&start, NULL);
  for (int x = 0; x < N; ++x)
    {
        int pid = fork() ;
        if (pid == 0)
          {
            for (int i = threadInfo[x].start; i < threadInfo[x].end ; ++i)
              {
                for (int j = 0; j < bCols; ++j)
                  {
                    for (int k = 0; k < aCols; ++k)
                            *(cPtr+i*bCols+j) += (*(aPtr+i*aCols+k))* (*(bPtr+k*bCols+j)) ;  //C[i][j] += A[i][k]*B[k][j]
                  }       
              }
            exit (0);
          } 
    }
   for (int x = 0; x < N; ++x)
          wait(NULL) ;

    gettimeofday (&end, NULL);
    //end timer
    if (interactive)
        output_matrix ();

    timeMicrosec = (end.tv_sec - start.tv_sec) * 1e6; 
    timeMicrosec = (timeMicrosec + (end.tv_usec-start.tv_usec));

    //detaching from the shared memory  
    shmdt (aPtr);
    shmdt (bPtr);
    shmdt (cPtr);

    // destroy the shared memory 
    shmctl (aId,IPC_RMID,NULL); 
    shmctl (bId,IPC_RMID,NULL); 
    shmctl (cId,IPC_RMID,NULL); 

    return (unsigned long long)timeMicrosec ;
}


int
main (int argc,
      char *argv[])
{
  int c;
  /* Loop through each option (and its's arguments) and populate variables */

  //printf("rip\n");
  while (1)
    {
      int this_option_optind = optind ? optind : 1;
      int option_index = 0;
      static struct option long_options[] =
        {
          {"help",        no_argument,            0, 'h'},
          {"ar",          required_argument,      0, '1'},
          {"ac",          required_argument,      0, '2'},
          {"br",          required_argument,      0, '3'},
          {"bc",          required_argument,      0, '4'},
          {"interactive", no_argument,            0, '5'},
          {0,             0,                      0,  0 }
        };

      c = getopt_long (argc,
                       argv, 
                       "h1:2:3:4:5",
                       long_options,
                       &option_index);
      if (c == -1)
                break;

      switch (c)
        {
        case 0:
          fprintf (stdout,
                   "option %s",
                   long_options[option_index].name);
          if (optarg)
                fprintf (stdout,
                         " with arg %s",
                         optarg);
          /*??*/fprintf (stdout, "\n");
          break;

        case '1':
          aRows = atoi (optarg);
          break;

        case '2':
          aCols = atoi (optarg);
          break;

        case '3':
          bRows = atoi (optarg);
          break;

        case '4':
          bCols = atoi (optarg);
          break;

        case '5':
          interactive = 1;
          break;

        case 'h':
        case '?':
          usage (argc,
                 argv);

        default:
          fprintf (stdout,
                   "?? getopt returned character code 0%o ??\n",
                   c);
          usage (argc,
                 argv);
        }
    }


    if (optind != argc)
      {
        fprintf (stderr,
                 "Unexpected arguments\n");
        usage (argc,
               argv);
      }

    if (aCols != bRows)
            exit(EXIT_FAILURE);


    unsigned long long time_single, time_multi_process, time_multi_thread;
       
    time_single = single_thread_mm() ;
    time_multi_thread = multi_thread_mm();
    time_multi_process = multi_process_mm();
    
    fprintf (stdout,
             "Time taken for single threaded: %llu us\n",
             time_single);

    fprintf (stdout,
             "Time taken for multi process: %llu us\n",
             time_multi_process);

    fprintf (stdout, 
             "Time taken for multi threaded: %llu us\n",
             time_multi_thread);

    fprintf (stdout,
             "Speedup for multi process : %4.2f x\n",
              (double)time_single/time_multi_process);

    fprintf (stdout,
             "Speedup for multi threaded : %4.2f x\n",
              (double)time_single/time_multi_thread);

    exit(EXIT_SUCCESS);
}







