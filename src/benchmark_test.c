#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <pthread.h>

#include "barrier.h"

#define N_THREADS 3

barrier_t my_barr;

void *print_from_thread(void *id_thread)
{
    int id = *(int*)id_thread;

    for (int i = 0; i <= 10; i++)
    {
        printf("Print %d from thread %d\n", i, id);
        barrier_wait(&my_barr);
    }

    return NULL;
}

int main(void)
{

    barrier_init(&my_barr, N_THREADS);

    pthread_t threads_handles[N_THREADS];
    int tid[N_THREADS];

    for (int i = 0; i < N_THREADS; i++)
    {
        tid[i] = i;
        pthread_create(&threads_handles[i], NULL, print_from_thread, (void *)&tid[i]);
    }

    for (int i = 0; i < N_THREADS; i++)
    {
        pthread_join(threads_handles[i], NULL);
    }

    barrier_destroy(&my_barr);

    return 0;
}