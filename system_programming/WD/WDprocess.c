#define _GNU_SOURCE
#include <stdio.h> /*printf*/
#include <pthread.h>/*pthread_create*/
#include <unistd.h>/*sleep*/
#include <signal.h> /*siginfo_t*/
#include <semaphore.h>/*sleep*/
#include <stdlib.h>/*getenv*/
#include <stdatomic.h>/*fetch_and_add*/
#include <assert.h>
#include <sys/types.h> /*siginfo_t*/
#include <fcntl.h> /* O_CREAT*/
#include "wd.h"
#include "../../ds/scheduler/scheduler.h"
#include "../../ds/uid/uid.h"

#define SUCCESS (0)

#define TRUE (1)
#define FALSE (0)
#define FAIL (-1)
#define RE_SCHEDUAL (0)
#define NUM_OF_SIG_PER_CHECK (10)

#define RUN (0)
#define STOP (1)

volatile sig_atomic_t stop_flag;
volatile sig_atomic_t counter;

typedef struct context
{
    pid_t send_to_pid;
    Scheduler_t *sched;
} context_ty;

int kill(pid_t pid, int sig);

/*-------- TASKS--------*/
int SendSignalTask(void *arg)
{
    atomic_fetch_add(&counter, 1);
    if(FAIL == kill(((context_ty *)arg)->send_to_pid, SIGUSR1))
    {
        printf("kill from WD APP fail\n");
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
int CloseAllSem()
{
    sem_t *wd_thread_sem =  sem_open("/wd_thread_sem", O_CREAT , 0666, 0);
    sem_t *wd_process_sem =  sem_open("/wd_process_sem", O_CREAT , 0666, 0); 
    if(SEM_FAILED == wd_thread_sem || SEM_FAILED == wd_process_sem )
    {
        printf("open wd sem failed in wd thread\n");
        return FAIL;
    }

    sem_close(wd_thread_sem);
    sem_close(wd_process_sem);
    return SUCCESS;
}

void SetToDefaultSignalHandlers()
{
    signal(SIGUSR1, SIG_DFL);
    signal(SIGUSR2, SIG_DFL);
}

void *CleanUp(context_ty *context)
{
    
    CloseAllSem();
    SchedulerDestroy(context->sched);

    return NULL;

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


int SetTasksInSched(context_ty *context)
{
    if(UIDIsSame(SchedulerAdd((context->sched), SendSignalTask, context, 1),UIDGetBadUid()))
    {
        printf("adding send task from wd process fail\n");
        return FAIL;
    }
    if(UIDIsSame(SchedulerAdd((context->sched), CheckCounterTask, context, 10),UIDGetBadUid()))
    {
        printf("adding send task from wd process fail\n");
        return FAIL;
    }
    return SUCCESS;
}


int UpdateSemaphoresValue()
{  
    sem_t *wd_thread_sem =  sem_open("/wd_thread_sem", O_CREAT , 0666, 0);
    sem_t *wd_process_sem =  sem_open("/wd_process_sem",  O_CREAT , 0666, 0); 

    if(SEM_FAILED == wd_thread_sem || SEM_FAILED == wd_process_sem )
    {
        printf("open wd sem failed in wd thread\n");
        return FAIL;
    }
    sem_post(wd_thread_sem);
    while (FAIL == sem_wait(wd_process_sem));
    return SUCCESS;
}

void UpdateEnv()
{
    char pid[20] = {0}; 
    sprintf(pid, "%d", getpid());
    if(FAIL == setenv("WD_ID", pid, 1))
    {
        printf("setenv failed\n");
    } 
}


int CreateMainProcess(char *const *argv)
{

    pid_t pid = fork();
    UpdateEnv();
    if(0 == pid)
    {
        execv(argv[0], argv + 1);
    }
 
    return pid;
}



int main(int argc, char **argv)
{
    context_ty context ={0};
    sem_t *sem = sem_open("/sem_stop",O_CREAT, 0666, 0);
    if(SEM_FAILED == sem)
    {
        printf("stop sem - sem open failed");
        return FAIL;
    }
    (void)argc;
    counter = 0;
    stop_flag = RUN;
    context.send_to_pid = getppid();
    context.sched = SchedulerCreate();

    if(NULL == context.sched)
    {
        printf("sched create fail\n");
        return FAIL;
    }
    if(SUCCESS != SetSignalHandlers())
    {
        return FAIL;
    }

    if(SUCCESS != SetTasksInSched(&context))
    {
        return FAIL;
    }

    if(SUCCESS != UpdateSemaphoresValue())
    {
        return FAIL;
    }
    printf("wd process id: %d\n",getpid());
    while(STOPPED == SchedulerRun(context.sched))
    {
        if(STOP == stop_flag)
        {
            sem_post(sem);
            sem_close(sem);
            CleanUp(&context);
            return SUCCESS;
        }
        context.send_to_pid = CreateMainProcess(argv);
        if(0 > context.send_to_pid)
        {
            printf("fork fail\n");
            exit(FAIL);
        }
        if(FAIL == context.send_to_pid)
        {
            return FAIL;
        }
        if(SUCCESS != UpdateSemaphoresValue())
        {
            return FAIL;
        }
    }

    return SUCCESS;

}