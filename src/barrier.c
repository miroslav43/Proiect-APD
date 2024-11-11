//FILE: barrier.c
#ifdef __APPLE__
#include "barrier.h"

int barrier_init(
    barrier_t *barrier,
    unsigned int count)
{
    if (0 == count)
    {
        errno = EINVAL;
        return -1;
    }

    if (0 > pthread_mutex_init(&barrier->mutex, 0))
    {
        return -1;
    }

    if (0 > pthread_cond_init(&barrier->cond, 0))
    {
        pthread_mutex_destroy(&barrier->mutex);
        return -1;
    }

    barrier->tripCount = count;
    barrier->count = 0;

    return 0;
} /* pthread_barrier_init() */

/* ------------------------------------------------------------------------- */

int barrier_destroy(
    barrier_t *barrier)
{
    pthread_cond_destroy(&barrier->cond);
    pthread_mutex_destroy(&barrier->mutex);
    return 0;
} /* pthread_barrier_destroy() */

/* ------------------------------------------------------------------------- */

int barrier_wait(
    barrier_t *barrier)
{
    pthread_mutex_lock(&barrier->mutex);
    ++(barrier->count);
    if (barrier->count >= barrier->tripCount)
    {
        barrier->count = 0;
        pthread_cond_broadcast(&barrier->cond);
        pthread_mutex_unlock(&barrier->mutex);
        return 1;
    }
    else
    {
        pthread_cond_wait(&barrier->cond, &(barrier->mutex));
        pthread_mutex_unlock(&barrier->mutex);
        return 0;
    }
} /* pthread_barrier_wait() */

#endif /* __APPLE__ */

/* :vi set ts=2 et sw=2: */