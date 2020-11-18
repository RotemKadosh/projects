#include <stdio.h> /*printf*/
#include <pthread.h>/*pthread_create*/
#include <unistd.h>/*sleep*/
#include <semaphore.h>/*sleep*/
#include <assert.h>
#include "../../ds/circular_buffer/circular_buffer.h"

#define CAPACITY (100)
#define SUCCESS (0)

pthread_mutex_t FSQ_lock = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_read;
sem_t sem_write;

typedef struct FSQ
{
    int arr[CAPACITY];
    size_t read;
    size_t write;

} FSQ_ty;

int FSQRead(FSQ_ty *fsq)
{
    int ans = fsq->arr[fsq->read];
    fsq->read = (fsq->read + 1) % CAPACITY; 
    return ans;
}

void FSQWrite(FSQ_ty *fsq, int num)
{
    fsq->arr[fsq->write] = num;
    fsq->write = (fsq->write + 1) % CAPACITY; 
}

void *Produser(void *arg)
{   
    static int counter = 0;
    sem_wait(&sem_write);
    pthread_mutex_lock(&FSQ_lock);
    FSQWrite((FSQ_ty *)arg, counter);
    printf("write: %d\n", counter);
    counter ++; 
    pthread_mutex_unlock(&FSQ_lock);
    sem_post(&sem_read);

    return NULL;
}


void *Consumer(void *arg)
{
    sem_wait(&sem_read);
    pthread_mutex_lock(&FSQ_lock);
    printf("read: %d\n", FSQRead((FSQ_ty *)arg));
    pthread_mutex_unlock(&FSQ_lock);
    sem_post(&sem_write);

    return NULL;
}

int main()
{
    pthread_t tid[100];
    size_t i = 0;
    FSQ_ty fsq;
    fsq.write = 0;
    fsq.read = 0;
    sem_init(&sem_write, 0, CAPACITY);
    sem_init(&sem_read, 0, 0);
    for(i = 0; i < 50; i++)
    {
        if(SUCCESS != pthread_create(&tid[i], NULL, Produser, (void *)&fsq))
        {
            printf("producer fail");
        }
    }
    for(i = 50; i < 100; i++)
    {
        if(SUCCESS != pthread_create(&tid[i], NULL, Consumer, (void *)&fsq))
        {
            printf("producer fail");
        }
    }
    for(i = 0; i < 100; i++)
    {
        pthread_join(tid[i], NULL);
    }
    sem_destroy(&sem_write);
    sem_destroy(&sem_read);
    pthread_mutex_destroy(&FSQ_lock);
    return 0;
}
