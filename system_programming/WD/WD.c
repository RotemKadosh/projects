#define _GNU_SOURCE
#include <stdio.h> /*printf*/
#include <pthread.h>/*pthread_create*/
#include <unistd.h>/*sleep*/
#include <signal.h> /*siginfo_t*/
#include <semaphore.h>/*sleep*/
#include <stdlib.h>/*getenv*/
#include <stdatomic.h>/*fetch_and_add*/
#include <sys/types.h> /*siginfo_t*/
#include <assert.h>
#include <fcntl.h> /* O_CREAT*/
#include "wd.h"
#include "../../ds/scheduler/scheduler.h"
#include "../../ds/uid/uid.h"


#define SUCCESS (0)
#define FAIL (-1)
#define RE_SCHEDUAL (0)
#define NUM_OF_SIG_PER_CHECK (10)
#define RUN (0)
#define STOP (1)

int kill(pid_t pid, int sig);

volatile sig_atomic_t counter;
volatile sig_atomic_t stop_flag;

typedef struct context
{   
    pid_t send_to_pid;
    Scheduler_t *sched;
    
} context_ty;


/*-------- TASKS--------*/
int SendSignalTask(void *arg)
{
    atomic_fetch_add(&counter, 1);
    if(FAIL == kill(((context_ty *)arg)->send_to_pid, SIGUSR1))
    {
        printf("kill from WD thread fail\n");
    }
    return RE_SCHEDUAL;
}

int CheckCounterTask(void *arg)
{
    if(NUM_OF_SIG_PER_CHECK <= counter || STOP == stop_flag)
    {
        SchedulerPause(((context_ty *)arg)->sched);
    }
    return RE_SCHEDUAL;
}


/*------cleanup functions----------*/


/*--------signal handlers--------*/
void Usr1SigHand(int sig, siginfo_t *inf, void *context)
{
    counter = 0;
    (void)sig;
    (void)inf;
    (void)context;
}

void Usr2SigHand(int sig, siginfo_t *inf, void *context)
{
 
    stop_flag = STOP;
    (void)sig;
    (void)inf;
    (void)context;
}
  


/*--------setup functions--------*/

pid_t CreateWdProcess(char *const *argv)
{
    pid_t pid = 0;
    pid = fork();
    if(0 == pid)
    {
        execv("wd.out", argv);
        printf("execv failed in threas");
    }

    return pid;
}

int SetSignalHandlers()
{
    int status = SUCCESS;
    struct sigaction usr1hand;
    struct sigaction usr2hand;
    

    usr1hand.sa_sigaction = Usr1SigHand;
    
    usr2hand.sa_sigaction = Usr2SigHand;

    status = sigaddset(&usr2hand.sa_mask, SIGUSR1);
    if(SUCCESS == status)
    {
        status = sigaction(SIGUSR1, &usr1hand, NULL);
        if(SUCCESS == status)
        {
            status = sigaction(SIGUSR2, &usr2hand, NULL);
        }

    }
    return status;

}

int SetTasksInSched( context_ty *context)
{
    if(UIDIsSame(SchedulerAdd(context->sched, SendSignalTask, context, 1), UIDGetBadUid()))
    {
        printf("adding send task from wd process fail\n");
        return FAIL;
    }
    if(UIDIsSame(SchedulerAdd(context->sched, CheckCounterTask, context, 10), UIDGetBadUid()))
    {
        printf("adding check task from wd process fail\n");
        return FAIL;
    }
    return SUCCESS;

}

int UpdateSemaphoresValue()
{  
    
    sem_t *wd_thread_sem =  sem_open("/wd_thread_sem", O_CREAT , 0666, 0);
    sem_t *wd_process_sem =  sem_open("/wd_process_sem", O_CREAT , 0666, 0); 
    
    if(SEM_FAILED == wd_thread_sem || SEM_FAILED == wd_process_sem )
    {
        printf("open wd sem failed in wd thread\n");
        return FAIL;
    }

    sem_post(wd_process_sem);
    while( FAIL == sem_wait(wd_thread_sem));
    return SUCCESS;
}

/*-------Thread function-------*/
int IsWDParentProcess()
{   
    char *wd_id = getenv("WD_ID");
    pid_t wd = 0;
    if(NULL != wd_id)
    {
        wd = atoi(wd_id);
    }
    return (wd == getppid());
}

void UnlinkAllSem()
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


void *CleanUp(context_ty *context)
{
    
    UnlinkAllSem();

    SchedulerDestroy(context->sched);
    return NULL;

}


void *WatchDogThreadFunc(void *arg)
{
    context_ty context = {0};
    sem_t *stop_sem;
    sem_t *wd_start_sem;
    
    counter = 0;
    stop_flag = RUN;

    wd_start_sem = sem_open("/wd_start_sem", O_CREAT , 0666, 0);
    if(SEM_FAILED == wd_start_sem)
    {
        return NULL;
    }
    if(!IsWDParentProcess())
    {
        context.send_to_pid = CreateWdProcess(arg);
        if(0 > context.send_to_pid)
        {
            return NULL;
        }
    }
    else
    {
        printf("my parent is WD\n");
        context.send_to_pid = getppid();
      
    }
    
    context.sched = SchedulerCreate();
    if(NULL == context.sched)
    {
        printf("sched create fail\n");
    }

    if(SUCCESS != SetSignalHandlers())
    {
        return NULL;
    }

    if(SUCCESS != SetTasksInSched(&context))
    {
        return NULL;
    }

    if(SUCCESS != UpdateSemaphoresValue())
    {
        return NULL;
    }
    sem_post(wd_start_sem);
    
    while(STOPPED == SchedulerRun(context.sched))
    {
        if(STOP == stop_flag)
        {
         
            kill(context.send_to_pid, SIGUSR2);
            CleanUp(&context);
            if(SEM_FAILED == (stop_sem = sem_open("/sem_stop", O_CREAT, 0666, 0)))
            {
                return NULL;
            }
            sem_post(stop_sem); 
            sem_close(stop_sem);  
            return NULL;
        }

        context.send_to_pid = CreateWdProcess(arg);
        if(FAIL == UpdateSemaphoresValue())
        {
            return NULL;
        }
    }
    
    return NULL;
}

/*-------API function-------*/
int StartWd( char **argv)
{
    pthread_t tid = 0;
    pthread_attr_t attr;
    sem_t *wd_start_sem = sem_open("/wd_start_sem", O_CREAT , 0666, 0);
    if(SEM_FAILED == wd_start_sem)
    {
        printf("sem open for start wd fail in wd start\n");
        return FAIL;
    }
    if (0 != pthread_attr_init(&attr)) 
    {
        perror("Attribute init failed\n");
        return FAIL;
    }
    if (0 != pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)) 
    {
        perror("Setting detached state failed\n");
        return FAIL;
    }
    if(SUCCESS != pthread_create(&tid, &attr, WatchDogThreadFunc, argv))
    {
        return FAIL;
    }
    while(FAIL == sem_wait(wd_start_sem))
    {
        printf("sem start wait fail");
    }
    return SUCCESS;
}

void StopWd()
{
    sem_t *sem = sem_open("/sem_stop", O_CREAT, 0666, 0);
    if(SEM_FAILED == sem)
    {
        printf("stop failed");
        return;
    }
    raise(SIGUSR2);
    sleep(2);
    while(FAIL == sem_wait(sem))
    {
        printf("stop wait sem failed\n");
    }
    while(FAIL == sem_wait(sem))
    {
        printf("stop wait sem failed\n");
    }
}

