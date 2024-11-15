#include <stdio.h>
#include <stdlib.h> // For atoi()
#include <pthread.h>
#include <time.h>
#include "benchmark_common.h"
#include "barrier.h"

my_barrier_t barrier;

int NUM_THREADS;
int REPEATS;

void *thread_func(void *arg)
{
    int thread_id = *(int *)arg;

    for (int i = 0; i < REPEATS; i++)
    {
        do_work(thread_id);
        barrier_wait(&barrier);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s NUM_THREADS REPEATS\n", argv[0]);
        return 69;
    }

    NUM_THREADS = atoi(argv[1]);
    REPEATS = atoi(argv[2]);

    pthread_t *threads = malloc(NUM_THREADS * sizeof(pthread_t));
    int *thread_ids = malloc(NUM_THREADS * sizeof(int));
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    barrier_init(&barrier, NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    barrier_destroy(&barrier);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec);
    elapsed += (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("%lf\n", elapsed); // Output elapsed time in seconds

    free(threads);
    free(thread_ids);

    return 0;
}
