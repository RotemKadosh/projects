#include <stdio.h> /*printf*/
#include <pthread.h>/*pthread_create*/
#include <unistd.h>/*sleep*/

#define ARR_SIZE (10)
#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)

static int arr[ARR_SIZE];
static size_t arr_size = 0;

/*-----------------declerations-------------------*/
void *Produser(void *arg);
void WriteToBuffer();
void *Consumer(void *arg);
void SumAndPrintBuffer();

/*----------------------definitions-----------------*/
void *Produser(void *arg)
{
    while (TRUE)
    {
        while (0 != arr_size){};
        WriteToBuffer(); 
    }
    return NULL;
}

void WriteToBuffer()
{
    static int counter = 0;
    size_t i = 0;
    for(i = 0; i < ARR_SIZE; i++)
    {
       arr[i] = counter; 
       ++arr_size;
    }
    ++counter;
}

void *Consumer(void *arg)
{
    while(TRUE)
    {
        while(ARR_SIZE != arr_size){};
        SumAndPrintBuffer();
    } 
    return NULL;
}

void SumAndPrintBuffer()
{
    int sum = 0;
    size_t i = 0;
    for(i = 0; i < ARR_SIZE; i++)
    {
       sum += arr[i]; 
       --arr_size;
    }
    printf("sum of arr is :%d\n", sum);  
}

int main()
{
    pthread_t pro_id = 0;
    pthread_t con_id = 0;
    if(SUCCESS != pthread_create(&pro_id, NULL, Produser, NULL))
    {
        printf("producer fail");
    }
    if(SUCCESS != pthread_create(&con_id, NULL, Consumer, NULL))
    {
        printf("Consumer fail");
    }
    pthread_join(pro_id, NULL);
    pthread_join(con_id, NULL);
    return 0;
}

