#include <stdio.h> /*printf*/
#include <pthread.h>/*pthread_create*/
#include <unistd.h>/*sleep*/
#include <semaphore.h>/*sleep*/
#include <assert.h>
#include "../../ds/circular_buffer/circular_buffer.h"

#define CAPACITY (5)
#define SUCCESS (0)

pthread_mutex_t FSQ_lock = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_read;

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
    pthread_mutex_lock(&FSQ_lock);
    FSQWrite((FSQ_ty *)arg, counter);
    printf("write: %d\n", counter);
    counter ++; 
    sem_post(&sem_read);
    pthread_mutex_unlock(&FSQ_lock);
    

    return NULL;
}


void *Consumer(void *arg)
{
    int sem_val = 0;
    int overflow = 0;
    int flag = 0;
    while(0 == flag)
    {
        pthread_mutex_lock(&FSQ_lock);
        sem_getvalue(&sem_read, &sem_val);
        if(0 < sem_val)
        {
            flag = 1;
            if(CAPACITY < sem_val)
            {
                overflow = (sem_val % CAPACITY);
                ((FSQ_ty *)arg)->read = (((FSQ_ty *)arg)->read + overflow) % CAPACITY;  
            }
            printf("read: %d\n", FSQRead((FSQ_ty *)arg));
            while(overflow  >= 0)
            {
                sem_wait(&sem_read);
                --overflow;
            }
        }
        pthread_mutex_unlock(&FSQ_lock);
    }
   
    


    return NULL;
}

int main()
{
    pthread_t tid[60];
    size_t i = 0;
    FSQ_ty fsq;
    fsq.write = 0;
    fsq.read = 0;
    sem_init(&sem_read, 0, 0);
    for(i = 0; i < 30; i++)
    {
        if(SUCCESS != pthread_create(&tid[i], NULL, Produser, (void *)&fsq))
        {
            printf("producer fail");
        }
        if(SUCCESS != pthread_create(&tid[i + 30], NULL, Consumer, (void *)&fsq))
        {
            printf("producer fail");
        }
    }
   
    for(i = 0; i < 60; i++)
    {
        pthread_join(tid[i], NULL);
    }

    sem_destroy(&sem_read);
    pthread_mutex_destroy(&FSQ_lock);
    return 0;
}
