#include <pthread.h>/*pthread*/
#include <stdlib.h> /*exit*/
#include <stdio.h> /*printf*/
#include <unistd.h>
#include <time.h>
#define SUCCESS (0)
#define FAIL (1)
#define THREADS (45)

static size_t global_array [32750] = {0};
static const size_t number = 1500000000;


void *ThreadFunc(void *argv)
{
    size_t sum = 0;
    size_t range = number / THREADS;
    size_t i = ((size_t)argv * range) + 1;
    size_t j = i;
    for(j = i ;j <= ((size_t)argv + 1) * range && j <= number; j++)
    {
        if(0 == number % j)
        {
            sum += j;
        }
    }
    global_array[(size_t)argv] = sum;
    return (void *)sum;
}

int ex123()
{

    size_t num = 0;
    pthread_t tid = 0;
    time_t end = 0;
    time_t start = time(NULL);

    pthread_attr_t *attr;
    pthread_attr_init(attr);
    pthread_attr_setdetachstate(attr, PTHREAD_CREATE_DETACHED);
    
    for(num = 0; num < 100000; num ++)
    {
        while(SUCCESS != pthread_create(&tid, attr, ThreadFunc, (void *)num)){sleep(1);}
    }
    end = time(NULL);
    printf("secondes: %ld\n", end - start);
    for(num = 0; num < 100000; num ++)
    {

            printf("%ld\n", global_array[num]);
            if(num != 0 && global_array[num] == 0)
            {
                break;
            }
    }
    return 0;
}

int ex4()
{
    size_t num = 0;
    time_t end = 0;
    time_t start = time(NULL);
    pthread_t tid_arr[32750] = {0};
    size_t sum = 0;
    size_t ret = 0;
    size_t lim = 32750;

    for(num = 0; num < lim; num++)
    {
        if(SUCCESS != pthread_create(&tid_arr[num], NULL, ThreadFunc, (void *)num))
        {
            printf("idx: %ld failed", num);
        }
    }
    for(num = 0; num < lim; num++)
    {
        if(SUCCESS != pthread_join(tid_arr[num], (void **)&ret))
        {
            printf("idx: %ld failed", num);
        }
        sum += ret;
    }

    printf("sum of devidors = %ld\n", sum);
    end = time(NULL);
    printf("secondes: %ld\n", end - start);
    return 0;
}

int ex5()
{
    
    size_t num = 0;
    time_t end = 0;
    time_t start = time(NULL); 
    size_t sum = 0;
    #pragma omp parallel for
    for(num = 1; num <= number; num++)
    {
        if(0 == number % num)
        {
            sum += num;
        }
    }

    printf("sum of devidors = %ld\n", sum);
    end = time(NULL);
    printf("secondes: %ld\n", end - start);
    return 0;
}

int main ()
{
    ex5();

    return 0;
}



