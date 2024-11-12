// FILE: barrier.h
#ifndef PTHREAD_BARRIER_H
#define PTHREAD_BARRIER_H

#include <pthread.h>
#include <errno.h>

typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int tripCount;
} my_barrier_t;

int barrier_init(my_barrier_t *barrier, 
                 unsigned int count);
int barrier_destroy(my_barrier_t *barrier);
int barrier_wait(my_barrier_t *barrier);



#endif /* PTHREAD_BARRIER_H */