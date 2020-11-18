#include <stdio.h> /*printf*/
#include <pthread.h>/*pthread_create*/
#include <unistd.h>/*sleep*/
#include <semaphore.h>/*sleep*/
#include <assert.h>
#include "../../ds/slist/slist.h"

#define NUM_OF_CONSUMERS (10)
#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int massage;
static int global_version;

/*-----------------declerations-------------------*/
void *Produser(void *arg);
void *Consumer(void *arg);


/*----------------------definitions-----------------*/
void *Produser(void *arg)
{   int i = 0;
    int local_massage = 0; 
    while(TRUE)
    {
        local_massage++;
        for(i = 0; i < NUM_OF_CONSUMERS; ++i)
        {
            sem_wait(&sem);
        }
        *(int *)arg = local_massage;
        pthread_mutex_lock(&lock);
        printf("write: %d\n", *(int *)arg);
        ++global_version;
        pthread_cond_broadcast(&cond);
        
        pthread_mutex_unlock(&lock);
    }
}



void *Consumer(void *arg)
{
    int local_version = 0;
    while (TRUE)
    {
        pthread_mutex_lock(&lock);
        sem_post(&sem);
        while(local_version == global_version)
        {
            pthread_cond_wait(&cond, &lock);
        }
        printf("read massage: %d\n", *(int *)arg);
        pthread_mutex_unlock(&lock);
        ++local_version;
    }
    return NULL;
}



int main()
{
    int massage;
    pthread_t tid[11];
    size_t i = 0;
    sem_init(&sem, 0, 0);
    global_version = 0;
    
    for(i = 0; i < 1; i++)
    {
        if(SUCCESS != pthread_create(&tid[i], NULL, Produser,(void *)&massage))
        {
            printf("producer fail");
        }
    }
    for(i = 1; i < 11; i++)
    {
        if(SUCCESS != pthread_create(&tid[i], NULL, Consumer,(void *)&massage))
        {
            printf("producer fail");
        }
    }
    for(i = 0; i < 11; i++)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    sem_destroy(&sem);
    return 0;
}

