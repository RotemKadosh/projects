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
#define ITS_ONE_TIME_THING (1)
#define NUM_OF_SIG_PER_CHECK (10)

#define RUN (0)
#define STOP (1)

static volatile sig_atomic_t stop_flag;
static volatile sig_atomic_t counter;

typedef struct context
{
    pid_t send_to_pid;
    Scheduler_t *sched;
    char *const *argv;
    char *path;   
} context_ty;

int kill(pid_t pid, int sig);
/*-------- declerations--------*/

int SendSignalTask(void *arg);
int CheckCounterTask(void *arg);
int ReviveTask(void *arg);
void Usr1SigHand(int sig);
void Usr2SigHand(int sig);
int CloseAllSem();
void CleanUp(context_ty *context);
int SetSignalHandlers();
int SetTasksInSched(context_ty *context);
int UpdateSemaphoresValue();
void UpdateEnv();
int CreateMainProcess(char *const *argv);
int ContextSetUp(context_ty *context , char **argv);
int WatchDogAppSetUp(context_ty *context , char **argv );
void StopApp(context_ty *context);

/*-------- TASKS--------*/

int SendSignalTask(void *arg)
{
    assert(NULL != arg);
    atomic_fetch_add(&counter, 1);
    if(FAIL == kill(((context_ty *)arg)->send_to_pid, SIGUSR1))
    {
        printf("kill from WD APP fail\n");
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
        }
    }
    return RE_SCHEDUAL;
}

int ReviveTask(void *arg)
{
    assert(NULL != arg);
    ((context_ty *)arg)->send_to_pid = CreateMainProcess(((context_ty *)arg)->argv);
    if(0 > ((context_ty *)arg)->send_to_pid)
    {
        printf("fork fail\n");
        return RE_SCHEDUAL;
    }
    if(SUCCESS != UpdateSemaphoresValue())
    {
        printf("semaphores update from wd process fail\n");
    }
    counter = 0;
    return ITS_ONE_TIME_THING;
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
        return FAIL;
    }
    if(FAIL == sem_post(wd_thread_sem))
    {
      return FAIL;  
    }
    while (FAIL == sem_wait(wd_process_sem));
    sem_close(wd_thread_sem);
    sem_close(wd_process_sem);
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
    pid_t pid;

    assert(NULL != argv);

    UpdateEnv();
    pid = fork();
    if(0 == pid)
    {
        execv(argv[0], argv + 1);
    }
 
    return pid;
}

int ContextSetUp(context_ty *context , char **argv)
{
    counter = 0;
    stop_flag = RUN;
    context->argv = argv;
    context->send_to_pid = getppid();
    context->sched = SchedulerCreate();
    if(NULL == context->sched)
    {
        return FAIL;
    }
    return SUCCESS;
}

int WatchDogAppSetUp(context_ty *context , char **argv )
{
    int status = 0;
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

/*--------cleanup functions--------*/

void CleanUp(context_ty *context)
{
    SchedulerDestroy(context->sched);
    CloseAllSem();
}

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

    sem_unlink("/wd_thread_sem");
    sem_unlink("/wd_process_sem");
    return SUCCESS;
}

void StopApp(context_ty *context)
{
    while(FAIL == kill(context->send_to_pid, SIGUSR2));
    CleanUp(context);
}
/*--------Main--------*/

int main(int argc, char **argv)
{
    int status = SUCCESS;
    context_ty context = {0};
    (void)argc;
    status = WatchDogAppSetUp(&context, argv);
    if(SUCCESS == status)
    {
        status = UpdateSemaphoresValue();
    }
    if(SUCCESS != status)
    {
        CleanUp(&context);
        return FAIL;
    }
    printf("I am WD APP, ID: %d\n", getpid());
    if(STOPPED == SchedulerRun(context.sched))
    {
        if(STOP == stop_flag)
        {
            StopApp(&context);
            return SUCCESS;
        }
    }
    exit(0);
    return SUCCESS;
}
