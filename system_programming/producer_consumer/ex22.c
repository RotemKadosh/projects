#include <stdio.h> /*printf*/
#include <pthread.h>/*pthread_create*/
#include <unistd.h>/*sleep*/
#include <semaphore.h>/*sleep*/
#include <assert.h>
#include "../../ds/slist/slist.h"

#define ARR_SIZE (10)
#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)

pthread_mutex_t slist_lock = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;

static void SlistPop(Slist_t *list)
{   
    Slist_iter_t iter = SlistRemove(SlistBegin(list));
    printf("next after poped: %d\n", (int)(size_t)SlistGetData(iter));
}
 
static void SlistPush(Slist_t *list, void *data)
{
    SlistInsert(SlistBegin(list), data); 
    printf("pushed: %d\n", (int)(size_t)data);
} 


/*-----------------declerations-------------------*/
void *Produser(void *arg);

void *Consumer(void *arg);


/*----------------------definitions-----------------*/
void *Produser(void *arg)
{   
    static int counter = 0;
    pthread_mutex_lock(&slist_lock);
    SlistPush((Slist_t *)arg, (void *)(size_t)counter);
    counter ++; 
    pthread_mutex_unlock(&slist_lock);
    sem_post(&sem);
    return NULL;
}


void *Consumer(void *arg)
{
    int flag = 0;

    sem_wait(&sem);
    pthread_mutex_lock(&slist_lock);
    SlistPop((Slist_t *)arg);
    pthread_mutex_unlock(&slist_lock);

    return NULL;
}

int main()
{
    pthread_t tid[100];
    size_t i = 0;
    Slist_t *list = SlistCreate();
    sem_init(&sem, 0, 0);
    for(i = 0; i < 50; i++)
    {
        if(SUCCESS != pthread_create(&tid[i], NULL, Produser, (void *)list))
        {
            printf("producer fail");
        }
    }
    for(i = 50; i < 100; i++)
    {
        if(SUCCESS != pthread_create(&tid[i], NULL, Consumer, (void *)list))
        {
            printf("producer fail");
        }
    }
    for(i = 0; i < 100; i++)
    {
        pthread_join(tid[i], NULL);
    }
    sem_destroy(&sem);
    pthread_mutex_destroy(&slist_lock);
    SlistDestroy(list);
    return 0;
}

