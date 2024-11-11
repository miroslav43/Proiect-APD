// FILE: barrier.h
#ifndef PTHREAD_BARRIER_H
#define PTHREAD_BARRIER_H
#ifdef __APPLE__

#include <pthread.h>
#include <errno.h>

typedef int pthread_barrierattr_t;

typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int tripCount;
} barrier_t;

int barrier_init(barrier_t *barrier, 
                 unsigned int count);
int barrier_destroy(barrier_t *barrier);
int barrier_wait(barrier_t *barrier);

/* :vi set ts=2 et sw=2: */

#endif /* __APPLE__ */
#endif /* PTHREAD_BARRIER_H */