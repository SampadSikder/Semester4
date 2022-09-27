#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define philosophers 5
#define chopSticks 5
sem_t stick[chopSticks];
void *dine(void *i)
{
    int n = *(int *)i;
    printf("\nPhilosopher % d is thinking ", n);
    sem_wait(&stick[n]);                       // left chopstick
    sem_wait(&stick[(n + 1) % chopSticks]);    // right chopstick
    printf("\nPhilosopher % d is eating ", n); // je age left right duitai nite parbe se ee khabe
    sleep(3);
    sem_post(&stick[n]);                             // put down left
    sem_post(&stick[(n + 1) % chopSticks]);          // put down right
    printf("\nPhilosopher % d Finished eating ", n); // stop eating
}
int main()
{
    pthread_t t[philosophers];
    // initialize semaphores
    for (int i = 0; i < chopSticks; i++)
    {
        sem_init(&stick[i], 0, 1);
    }
    for (int i = 0; i < philosophers; i++) // iinfinite loop chalano jay
    {
        int *no = (int *)malloc(sizeof(int));
        *no = i;
        pthread_create(&t[i], NULL, dine, (void *)no);
    }
    for (int i = 0; i < philosophers; i++)
    {
        pthread_join(t[i], NULL);
    }
    // destroy semaphores
    for (int i = 0; i < chopSticks; i++)
    {
        sem_destroy(&stick[i]);
    }
}