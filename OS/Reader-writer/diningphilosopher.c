#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define philosophers 5
#define chopSticks 5
pthread_mutex_t stick[chopSticks] = {PTHREAD_MUTEX_INITIALIZER};
void *dine(void *i)
{
    int n = *(int *)i;
    printf("\nPhilosopher % d is thinking ", n);

    // Philosopher picks up the left chopstick (wait)
    pthread_mutex_lock(&stick[n]);

    // Philosopher picks up the right chopstick (wait)
    pthread_mutex_lock(&stick[(n + 1) % chopSticks]);

    // After picking up both the chopstick philosopher starts eating
    printf("\nPhilosopher % d is eating ", n);
    sleep(3);

    // Philosopher places down the left chopstick (signal)
    pthread_mutex_unlock(&stick[n]);

    // Philosopher places down the right chopstick (signal)
    pthread_mutex_unlock(&stick[(n + 1) % chopSticks]);

    // Philosopher finishes eating
    printf("\nPhilosopher % d Finished eating ", n);
}
int main()
{
    pthread_t t[philosophers];

    for (int i = 0; i < philosophers; i++)
    {
        int *no = (int *)malloc(sizeof(int));
        *no = i + 1;
        pthread_create(&t[i], NULL, dine, (void *)no);
    }
    for (int i = 0; i < philosophers; i++)
    {
        pthread_join(t[i], NULL);
    }
}