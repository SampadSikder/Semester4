#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#define readers 5
#define writers 5
sem_t resource, readTry;
pthread_mutex_t rmutex = PTHREAD_MUTEX_INITIALIZER, wmutex = PTHREAD_MUTEX_INITIALIZER;
int cnt = 1;
int numreader = 0;
int numwriter = 0;
void *writer(void *wno)
{
    pthread_mutex_lock(&wmutex);
    numwriter++;
    printf("Number of writers: %d trying to write\n", numwriter);
    if (numwriter == 1)
        sem_wait(&readTry); // lock writers if first writer
    pthread_mutex_unlock(&wmutex);
    sem_wait(&resource); // resource lock acquire to write
    // critical section
    cnt = cnt * 2;
    printf("Writer %d modified cnt to %d\n", (*((int *)wno)), cnt);
    sem_post(&resource);
    // mutex lock to edit num writer
    pthread_mutex_lock(&wmutex);
    numwriter--;
    if (numwriter == 0) // last writer
        sem_post(&readTry);
    pthread_mutex_unlock(&wmutex);
    // exit
}
void *reader(void *rno)
{
    sem_wait(&readTry);          // lock writer
    pthread_mutex_lock(&rmutex); // reader lock so that another reader cannot enter
    numreader++;
    printf("Number of reader:%d trying to read\n", numreader);
    if (numreader == 1)
    {
        sem_wait(&resource); // 1ta reader holeo lock writer
    }
    pthread_mutex_unlock(&rmutex);
    sem_post(&readTry);                                        // writer re dhokar chance? Yes
    printf("Reader %d: read cnt as %d\n", *((int *)rno), cnt); // reader read
    pthread_mutex_lock(&rmutex);
    numreader--;
    if (numreader == 0)
    {
        sem_post(&resource); // If this is the last reader, it releases the lock for writer.
    }
    pthread_mutex_unlock(&rmutex);
}

int main()
{

    pthread_t read[readers], write[writers];
    sem_init(&resource, 0, 1);
    sem_init(&readTry, 0, 1);
    // int *no = (int *)malloc(sizeof(int));
    for (int i = 0; i < readers; i++)
    {
        int *no = (int *)malloc(sizeof(int));
        *no = i + 1;
        pthread_create(&read[i], NULL, (void *)reader, (void *)no);
        pthread_create(&write[i], NULL, (void *)writer, (void *)no);
    }
    for (int i = 0; i < writers; i++)
    {
        pthread_join(write[i], NULL);
        pthread_join(read[i], NULL);
    }

    pthread_mutex_destroy(&wmutex);
    pthread_mutex_destroy(&rmutex);
    sem_destroy(&resource);
    sem_destroy(&readTry);
    return 0;
}