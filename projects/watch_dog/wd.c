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
#define NUM_OF_SIG_PER_CHECK (7)
#define RUN (0)
#define STOP (1)
#define ITS_ONE_TIME_THING (1)

int kill(pid_t pid, int sig);

static volatile sig_atomic_t counter;
static volatile sig_atomic_t stop_flag;
static pid_t send_to_pid;

typedef struct context
{   
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
int StopThread(context_ty *context );
int ContextSetUp(context_ty *context , char **argv);
int WatchDogThreadSetUp(context_ty *context , char **argv );
int SetWatchDogProcess(void *arg);
int CreateWDThread(char **argv);

/*-------- TASKS--------*/
int SendSignalTask(void *arg)
{
    assert(NULL != arg);
    
    atomic_fetch_add(&counter, 1);
    if(FAIL == kill(send_to_pid, SIGUSR1))
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
    else if(NUM_OF_SIG_PER_CHECK <= counter)
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
    counter = 0;
    return ITS_ONE_TIME_THING;
}

/*------cleanup functions----------*/
int StopThread(context_ty *context )
{
    sem_t *wd_start_sem = sem_open("/wd_start_sem", O_CREAT , 0666, 0);
    if(SEM_FAILED == wd_start_sem)
    {
        return FAIL;
    } 
    CleanUp(context);
    sem_post(wd_start_sem); 
    sem_close(wd_start_sem);  
    return SUCCESS;
}

void CleanUp(context_ty *context)
{
    if(NULL != context->sched)
    {
        SchedulerDestroy(context->sched);
    }
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
    struct sigaction usr1hand = {0};
    struct sigaction usr2hand = {0};
    
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

int SetTasksInSched(context_ty *context)
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
        perror("WD 241");  
    }
    while( FAIL == sem_wait(wd_thread_sem));
    sem_close(wd_thread_sem);
    sem_close(wd_process_sem);
    return SUCCESS;
}

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

int ContextSetUp(context_ty *context , char **argv)
{
    counter = 0;
    stop_flag = RUN;
    context->argv = argv;
    context->sched = SchedulerCreate();
    if(NULL == context->sched)
    {
        return FAIL;
    }
    return SUCCESS;
}

int WatchDogThreadSetUp(context_ty *context , char **argv )
{
    int status = SUCCESS;
    status = ContextSetUp(context, argv);
    if(SUCCESS == status)
    {
        status = SetSignalHandlers();
        if(SUCCESS == status)
        {
            status = SetTasksInSched(context);
        }
    }
    return status;
}

int SetWatchDogProcess(void *arg)
{
    if(!IsWDParentProcess())
    {
        send_to_pid = CreateWdProcess(arg);
        if(0 > send_to_pid)
        {
            return FAIL;
        }
    }
    else
    {
        send_to_pid = getppid();
    }
    return SUCCESS;
}

int CreateWDThread(char **argv)
{
    pthread_t tid = 0;
    pthread_attr_t attr;
    int status = 0;
    assert(NULL != argv);

    status = pthread_attr_init(&attr);
    if (SUCCESS == status) 
    {
        status = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        if (SUCCESS == status)
        {
            status = pthread_create(&tid, &attr, WatchDogThreadFunc, argv);
        }
    }
    return status;
}

/*-------Thread function-------*/

void *WatchDogThreadFunc(void *arg)
{
    context_ty context = {0};
    int status = SUCCESS;
    sem_t *wd_start_sem;

    assert(NULL != arg);

    wd_start_sem = sem_open("/wd_start_sem", O_CREAT , 0666, 0);
    if(SEM_FAILED == wd_start_sem)
    {
        return NULL;
    } 
    status = SetWatchDogProcess(arg);
    if(SUCCESS == status)
    {
        status = WatchDogThreadSetUp(&context, arg);
        if(SUCCESS == status)
        {
            status = UpdateSemaphoresValue();
        }
    }
    if(SUCCESS != status)
    {
        CleanUp(&context);
        return NULL;
    }
    sem_post(wd_start_sem);

    if(STOPPED == SchedulerRun(context.sched))
    {
        if(STOP == stop_flag)
        {
            StopThread(&context);
            return NULL;
        } 
        else
        {
            exit(FAIL);
        }
    }
    return NULL;
}

/*-------API function-------*/

int StartWd(char **argv)
{
    int status = SUCCESS;
    sem_t *wd_start_sem = sem_open("/wd_start_sem", O_CREAT , 0666, 0);
    if(SEM_FAILED == wd_start_sem)
    {
        printf("sem open for start wd fail in wd start\n");
        return FAIL;
    }
    status = CreateWDThread(argv);
    if(SUCCESS != status)
    {
        return status;
    }
    while(FAIL == sem_wait(wd_start_sem));
    sem_close(wd_start_sem);
    return SUCCESS;
}

void StopWd()
{
    sem_t *start_sem = sem_open("/wd_start_sem", O_CREAT, 0666, 0);
    if(SEM_FAILED == start_sem)
    {
        return;
    }
    while(FAIL == kill(send_to_pid, SIGUSR2));
    while(FAIL == sem_wait(start_sem))
    {
        perror("WD.c 354");
    }
    sem_close(start_sem);
    UnlinkAllSem();
}

