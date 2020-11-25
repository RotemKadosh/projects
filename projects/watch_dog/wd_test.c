#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include "wd.h"
#include "../../ds/utils/test.h"
#include <fcntl.h> /* O_CREAT*/
void UnlinkAllSem1()
{
    sem_t *wd_thread_sem =  sem_open("/wd_thread_sem", O_CREAT , 0666, 0);
    sem_t *wd_process_sem =  sem_open("/wd_process_sem", O_CREAT , 0666, 0); 
    sem_t *wd_start_sem = sem_open("/wd_start_sem", O_CREAT , 0666, 0);

    if(SEM_FAILED == wd_thread_sem || SEM_FAILED == wd_process_sem || SEM_FAILED == wd_start_sem)
    {
        printf("open wd sem failed in wd thread\n");
        return;
    }

    sem_close(wd_thread_sem);
    sem_close(wd_process_sem);
    sem_close(wd_start_sem);

    sem_unlink("/wd_thread_sem");
    sem_unlink("/wd_process_sem");
    sem_unlink("/wd_start_sem");
}


int main(int argc, char **argv)
{

    int sleep_time = 15;
    size_t num = 9999999999;
    StartWd(argv);
    printf("I Am the Main Process, I am alive, id : %d\n", getpid());
    while(sleep_time > 0)
    {
        sleep_time = sleep(sleep_time);
    }
    while(num > 0)
    {
        --num;
    }
 
    StopWd();

    (void)argc;
    printf("bye\n");
    return 0;
}
