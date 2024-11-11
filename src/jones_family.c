// jones_family.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "barrier.h"

#define NUM_DAYS 5

typedef struct
{
    char name[20];
} family_member_t;

barrier_t breakfast_barrier;
barrier_t dinner_barrier;
barrier_t math_study_barrier;
barrier_t football_barrier;

void *mama_papa_routine(void *arg)
{
    family_member_t *member = (family_member_t *)arg;

    for (int day = 1; day <= NUM_DAYS; day++)
    {
        printf("%s wakes up on day %d.\n", member->name, day);

        printf("%s is ready for breakfast.\n", member->name);
        barrier_wait(&breakfast_barrier);
        printf("%s is having breakfast with family.\n", member->name);

        printf("%s goes to work.\n", member->name);
        sleep(1); 
        printf("%s finishes work.\n", member->name);

        printf("%s is ready to eat dinner with family.\n", member->name);
        barrier_wait(&dinner_barrier);
        printf("%s is having dinner with family.\n", member->name);

        printf("%s goes to sleep.\n\n", member->name);
    }
    return NULL;
}

void *alice_bob_routine(void *arg)
{
    family_member_t *member = (family_member_t *)arg;
    int is_alice = strcmp(member->name, "Alice") == 0;

    for (int day = 1; day <= NUM_DAYS; day++)
    {
        printf("%s wakes up on day %d.\n", member->name, day);

        printf("%s is ready for breakfast.\n", member->name);
        barrier_wait(&breakfast_barrier);
        printf("%s is having breakfast with family.\n", member->name);

        printf("%s goes to school.\n", member->name);
        sleep(1); 
        printf("%s finishes school.\n", member->name);

        printf("%s walks home.\n", member->name);

        printf("%s is ready to learn math with %s.\n", member->name, is_alice ? "Bob" : "Alice");
        barrier_wait(&math_study_barrier);
        printf("%s learns math with %s.\n", member->name, is_alice ? "Bob" : "Alice");

        printf("%s is ready to eat dinner with family.\n", member->name);
        barrier_wait(&dinner_barrier);
        printf("%s is having dinner with family.\n", member->name);

        printf("%s goes to sleep.\n\n", member->name);
    }
    return NULL;
}

void *chris_dave_routine(void *arg)
{
    family_member_t *member = (family_member_t *)arg;
    int is_chris = strcmp(member->name, "Chris") == 0;

    for (int day = 1; day <= NUM_DAYS; day++)
    {
        printf("%s wakes up on day %d.\n", member->name, day);

        printf("%s is ready for breakfast.\n", member->name);
        barrier_wait(&breakfast_barrier);
        printf("%s is having breakfast with family.\n", member->name);

        printf("%s goes to school.\n", member->name);
        sleep(1);
        printf("%s finishes school.\n", member->name);

        printf("%s walks home.\n", member->name);

        printf("%s is ready to play football with %s.\n", member->name, is_chris ? "Dave" : "Chris");
        barrier_wait(&football_barrier);
        printf("%s plays football with %s.\n", member->name, is_chris ? "Dave" : "Chris");

        printf("%s is ready to eat dinner with family.\n", member->name);
        barrier_wait(&dinner_barrier);
        printf("%s is having dinner with family.\n", member->name);

        printf("%s goes to sleep.\n\n", member->name);
    }
    return NULL;
}

int main()
{
    pthread_t threads[6];
    family_member_t members[6] = {
        {"Mama Jones"},
        {"Papa Jones"},
        {"Alice"},
        {"Bob"},
        {"Chris"},
        {"Dave"}};

    barrier_init(&breakfast_barrier, 6);
    barrier_init(&dinner_barrier, 6);
    barrier_init(&math_study_barrier, 2);
    barrier_init(&football_barrier, 2);

    pthread_create(&threads[0], NULL, mama_papa_routine, &members[0]);
    pthread_create(&threads[1], NULL, mama_papa_routine, &members[1]);
    pthread_create(&threads[2], NULL, alice_bob_routine, &members[2]);
    pthread_create(&threads[3], NULL, alice_bob_routine, &members[3]);
    pthread_create(&threads[4], NULL, chris_dave_routine, &members[4]);
    pthread_create(&threads[5], NULL, chris_dave_routine, &members[5]);

    for (int i = 0; i < 6; i++)
    {
        pthread_join(threads[i], NULL);
    }

    barrier_destroy(&breakfast_barrier);
    barrier_destroy(&dinner_barrier);
    barrier_destroy(&math_study_barrier);
    barrier_destroy(&football_barrier);

    return 0;
}
