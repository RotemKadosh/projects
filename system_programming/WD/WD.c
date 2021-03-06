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
#define ITS_ONE_TIME_THING (1)

int kill(pid_t pid, int sig);

volatile sig_atomic_t counter;
volatile sig_atomic_t stop_flag;
volatile pid_t send_to_pid;
typedef struct context
{   
    pid_t send_to_pid;
    Scheduler_t *sched;
    char *const *argv;
    char *path;

} context_ty;
/*---------------decleration--------*/
int SendSignalTask(void *arg);
int CheckCounterTask(void *arg);
int ReviveTask(void *arg);
void Usr1SigHand(int sig);
void Usr2SigHand(int sig);
pid_t CreateWdProcess(char *const *argv);
int SetSignalHandlers();
int SetTasksInSched( context_ty *context);
int UpdateSemaphoresValue();
int IsWDParentProcess();
void UnlinkAllSem();
void CleanUp(context_ty *context);
void *WatchDogThreadFunc(void *arg);
int StartWd( char **argv);
void StopWd();

/*-------- TASKS--------*/
int SendSignalTask(void *arg)
{
    assert(NULL != arg);
    atomic_fetch_add(&counter, 1);
    if(FAIL == kill(((context_ty *)arg)->send_to_pid, SIGUSR1))
    {
        printf("kill from WD thread fail\n");
    }
    return RE_SCHEDUAL;
}

int CheckCounterTask(void *arg)
{
    assert(NULL != arg);
    if(STOP == stop_flag)
    {
        SchedulerPause(((context_ty *)arg)->sched);
    }
    else if(NUM_OF_SIG_PER_CHECK <= counter )
    {
        if(UIDIsSame(SchedulerAdd((((context_ty *)arg)->sched), ReviveTask, arg, 0),UIDGetBadUid()))
        {
            SchedulerPause(((context_ty *)arg)->sched);
            printf("adding revive task from main process fail\n");
        }

    }
    return RE_SCHEDUAL;
}

int ReviveTask(void *arg)
{
    send_to_pid = CreateWdProcess(((context_ty *)arg)->argv);
    if(0 > send_to_pid)
    {
        printf("fork fail\n");
        return RE_SCHEDUAL;
    }
    if(SUCCESS != UpdateSemaphoresValue())
    {
        printf("semaphores fail in revive task fail\n");
    }
    return ITS_ONE_TIME_THING;
}
/*------cleanup functions----------*/


/*--------signal handlers--------*/
void Usr1SigHand(int sig)
{
    counter = 0;
    (void)sig;
 
}

void Usr2SigHand(int sig)
{
 
    stop_flag = STOP;
    (void)sig;

}
  
/*--------setup functions--------*/

pid_t CreateWdProcess(char *const *argv)
{
    pid_t pid = 0;

    assert(NULL != argv);

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
    
    usr1hand.sa_handler = Usr1SigHand;
    
    usr2hand.sa_handler = Usr2SigHand;

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
        perror("open wd sem failed in wd thread\n");
        return FAIL;
    }
    if(FAIL == sem_post(wd_process_sem))
    {
      perror("WD 204");  
    }
    while( FAIL == sem_wait(wd_thread_sem))
    {}
    sem_close(wd_thread_sem);
    sem_close(wd_process_sem);
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

void CleanUp(context_ty *context)
{
    SchedulerDestroy(context->sched);

}


void *WatchDogThreadFunc(void *arg)
{
    context_ty context = {0};
    sem_t *wd_start_sem = sem_open("/wd_start_sem", O_CREAT , 0666, 0);
    counter = 0;
    stop_flag = RUN;
    if(SEM_FAILED == wd_start_sem)
    {
        perror("open wd sem failed in wd thread\n");
        return NULL;
    }
    if(!IsWDParentProcess())
    {
        send_to_pid = CreateWdProcess(arg);
        if(0 > send_to_pid)
        {
            return NULL;
        }
    }
    else
    {
        send_to_pid = getppid();
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
            CleanUp(&context);
            sem_post(wd_start_sem); 
            sem_close(wd_start_sem);  
            return NULL;
        }
        else
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
        printf("Attribute init failed\n");
        return FAIL;
    }

    if (0 != pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)) 
    {
        printf("Setting detached state failed\n");
        return FAIL;
    }

    if(SUCCESS != pthread_create(&tid, &attr, WatchDogThreadFunc, argv))
    {
        return FAIL;
    }
    while(FAIL == sem_wait(wd_start_sem))
    {
        perror("WD.c 335");  
    }
  
    sem_close(wd_start_sem);
    return SUCCESS;
}

void StopWd()
{
    sem_t *start_sem = sem_open("/wd_start_sem", O_CREAT, 0666, 0);
    if(SEM_FAILED == start_sem)
    {
        perror("WD.c 347");
        return;
    }
    while (FAIL == kill(send_to_pid, SIGUSR2))
    {
    }
    sleep(2);
    while(FAIL == sem_wait(start_sem))
    {
        perror("WD.c 354");
    }
    sem_close(start_sem);
    UnlinkAllSem();
}

