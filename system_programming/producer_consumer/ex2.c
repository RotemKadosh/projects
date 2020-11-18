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
    return NULL;
}

int SlistIsEmpty(Slist_t *list)
{
   return SlistIsSameIter(SlistBegin(list),SlistEnd(list));
}


void *Consumer(void *arg)
{
    int flag = 0;
    while (0 == flag)
    {
        pthread_mutex_lock(&slist_lock);
        if(!SlistIsSameIter(SlistBegin((Slist_t *)arg),SlistEnd((Slist_t *)arg)))
        {
            flag = 1;
            SlistPop((Slist_t *)arg);
        }
        pthread_mutex_unlock(&slist_lock);
    }
    return NULL;
}



int main()
{
    pthread_t tid[12];
    size_t i = 0;
    Slist_t *list = SlistCreate();
    for(i = 0; i < 6; i++)
    {
        if(SUCCESS != pthread_create(&tid[i], NULL, Produser, (void *)list))
        {
            printf("producer fail");
        }
    }
    for(i = 6; i < 12; i++)
    {
        if(SUCCESS != pthread_create(&tid[i], NULL, Consumer, (void *)list))
        {
            printf("producer fail");
        }
    }
    for(i = 0; i < 12; i++)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&slist_lock);
    SlistDestroy(list);
    return 0;
}

