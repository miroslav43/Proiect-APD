//FILE: benchmark_pthread.c
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "benchmark_common.h"
#include "barrier.h"

pthread_barrier_t barrier;

void* thread_func(void* arg) {
    int thread_id = *(int*)arg;

    for (int i = 0; i < REPEATS; i++) {
        do_work(thread_id);
        barrier_wait(&barrier);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    barrier_init(&barrier, NUM_THREADS);



    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }


    barrier_destroy(&barrier);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec);
    elapsed += (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Elapsed time with pthread_barrier: %lf ms\n", elapsed);

    return 0;
}
