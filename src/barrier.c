#include "barrier.h"

// Inițializează o barieră pentru sincronizarea thread-urilor
int barrier_init(
    my_barrier_t *barrier,
    unsigned int count)
{
    // Verificăm dacă count este zero (ar fi invalid)
    if (0 == count)
    {
        errno = EINVAL; // Setăm eroarea la "Invalid argument"
        return -1;
    }

    // Inițializăm mutex-ul pentru a proteja accesul la structura barierei
    if (0 > pthread_mutex_init(&barrier->mutex, 0))
    {
        return -1; // Dacă nu reușim să inițializăm mutex-ul, returnăm eroare
    }

    // Inițializăm condiția (cond) pentru a sincroniza thread-urile la barieră
    if (0 > pthread_cond_init(&barrier->cond, 0))
    {
        pthread_mutex_destroy(&barrier->mutex); // Distrugem mutex-ul dacă cond eșuează
        return -1;
    }

    // Setăm tripCount la numărul de thread-uri care trebuie să ajungă la barieră
    barrier->tripCount = count;
    // Inițial, niciun thread nu a ajuns la barieră, deci count e 0
    barrier->count = 0;

    return 0; // Returnăm succesul
}

// Distruge resursele asociate barierei
int barrier_destroy(
    my_barrier_t *barrier)
{
    // Distrugem condiția (cond) și mutex-ul
    pthread_cond_destroy(&barrier->cond);
    pthread_mutex_destroy(&barrier->mutex);
    return 0;
}

// Funcție principală a barierei - thread-urile se blochează aici până când toate ajung la barieră
int barrier_wait(
    my_barrier_t *barrier)
{
    // Intrăm în secțiunea protejată de mutex
    pthread_mutex_lock(&barrier->mutex);
    ++(barrier->count); // Incrementăm contorul pentru fiecare thread care ajunge la barieră

    // Dacă numărul de thread-uri care au ajuns e egal cu tripCount, toate pot merge mai departe
    if (barrier->count >= barrier->tripCount)
    {
        barrier->count = 0;                     // Resetăm contorul pentru următoarea utilizare a barierei
        pthread_cond_broadcast(&barrier->cond); // Trezim toate thread-urile care așteaptă la barieră
        pthread_mutex_unlock(&barrier->mutex);  // Eliberăm mutex-ul
        return 1;                               // Returnăm 1 pentru a indica ultimul thread care a ajuns la barieră
    }
    else
    {
        // Dacă nu au ajuns toate thread-urile, așteptăm
        pthread_cond_wait(&barrier->cond, &(barrier->mutex)); // Ne blocăm până când suntem treziți
        pthread_mutex_unlock(&barrier->mutex);                // Eliberăm mutex-ul când ieșim din așteptare
        return 0;                                             // Returnăm 0 pentru thread-urile care au așteptat
    }
}
