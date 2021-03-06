#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <limits.h>
#include <unistd.h>

#define NUM_THREADS 50
#define SIZE 16000

// Global Variables ------------------
unsigned int bigger;
unsigned int smallest; 
unsigned int threadThatFoundBigger;
unsigned int threadThatFoundSmallest;

typedef struct array
{
    unsigned int * array;
    int lenght;

} tpArray;

tpArray * listOfNumbers = NULL;
//------------------------------------


void * search(void * threadID)
{
    int threadId, interval;

    threadId = *((int *)threadID);
    interval = SIZE / NUM_THREADS;
    
    for (int i = threadId*interval; i < (1 + threadId)*interval; i++)
    {
        if (listOfNumbers->array[i] > bigger)
        {
            bigger = listOfNumbers->array[i];
            threadThatFoundBigger = threadId;
        }
        else if (listOfNumbers->array[i] < smallest)
        {
            smallest = listOfNumbers->array[i];
            threadThatFoundSmallest = threadId;
        }
    }

    pthread_exit(NULL); /* not necessary */
}

void iniciar_aleatorio(void)
{
    srand((unsigned int)time(NULL));
    rand();
    rand();
    rand();
}

unsigned int aleatorio(unsigned int a, unsigned int b)
{
    double r;
    r = (double) rand()/RAND_MAX;
    return (unsigned int)(a + r*(b-a));
}

void inicializeArray(void)
{
    listOfNumbers = (tpArray * ) malloc (sizeof(tpArray));

     if (listOfNumbers == NULL)
    {
        puts("Erro de memória!");
        exit(-1);
    }

    listOfNumbers->array = (unsigned int *) malloc (SIZE * sizeof(unsigned int));

    if (listOfNumbers->array == NULL)
    {
        puts("Erro de memória!");
        exit(-1);
    }

    listOfNumbers->lenght = SIZE;
    iniciar_aleatorio();
    
    for (int i = 0; i < listOfNumbers->lenght; i++)
    {
        listOfNumbers->array[i] = aleatorio(0, UINT_MAX);
    }
}


int main(int argc, char * argv[])
{
    pthread_t threads[NUM_THREADS];
    double ticks[2], takenTime;
    struct timeval tim;
    int * t = (int *) malloc (NUM_THREADS*sizeof(int));
    int i;

    inicializeArray();
    
    bigger = listOfNumbers->array[0];
    smallest = listOfNumbers->array[0];
    
    gettimeofday(&tim, NULL);
    ticks[0] = tim.tv_sec+(tim.tv_usec/1000000.0);
    
    for (i = 0 ; i < NUM_THREADS ; i++)
    {
        *t = i;
        pthread_create(&threads[*t], NULL, search, (void *)t);
        t++;
    }
    
    for(i = 0 ; i < NUM_THREADS ; i++)
    {
        pthread_join(threads[i], NULL); /* wait for all the threads to terminate */
    }

    gettimeofday(&tim, NULL);
    ticks[1] = tim.tv_sec+(tim.tv_usec/1000000.0);

    takenTime = (double) (ticks[1] - ticks[0]);
    
    printf("Taken time: %f sec -----------------------------------------------\n", takenTime);
    printf("Thread that found the bigger integer: %d - Bigger number: %u\n", threadThatFoundBigger, bigger);
    printf("Thread that found the smallest integer: %d - Smallest number: %u\n", threadThatFoundSmallest, smallest);
    puts("-----------------------------------------------------------------------");
    return 0;
}
