#include <sys/sem.h> /*semget*/
#include <stdio.h>   /*printf, fgets*/
#include <string.h>  /*strcmp, strtok*/
#include <stdlib.h>  /*atoi*/
#include <assert.h>  /*assert*/
#include <errno.h>

#define TRUE (0)
#define NUM_OF_SEM_IN_SET (1)
#define PATH ("/home/rotemkadosh27/git/system_programming/dummy.md")

typedef enum status
{
    SUCCESS,
    FAIL = -1
}status;

typedef int (*SemOperation)(int sid, int number, int undo);

union semun 
{
    int val;                /* value for SETVAL */
    struct semid_ds *buf;   /* buffer for IPC_STAT & IPC_SET */
    unsigned short *array;  /* array for GETALL & SETALL */
    struct seminfo *__buf;  /* buffer for IPC_INFO */
    void *__pad;
};


/*----------Declerations------------------------*/
int CreateSemaphore(char *proj_id);
static int GetSemVal(int sid, int number, int undo);
int DecreaseSemVal(int sid, int number, int undo);
int IncreaseSemVal(int sid, int number ,int undo);
static void GetArgs(char *c, int *number, int *undo_flag);
static int BinarySemInit(int semid);
static int InvalidInput(int sid, int number, int undo);
static void InitOpLut(SemOperation *operation_lut);
static int Exit(int sid, int number ,int undo);
/*---------------------definition-----------------------------*/

int CreateSemaphore(char *proj_id)
{
    int semid = 0;
    key_t key = 0;
    if((key_t)FAIL == (key = ftok(PATH, atoi(proj_id))))
    {
        printf("ftok fail");
        return FAIL;
    }
    if(FAIL == (semid = semget(key, 1, IPC_EXCL | IPC_CREAT | 0600 )))
    {
        if (EEXIST == errno)
        {
            semid = semget(key, 1, 0);
            if (FAIL == semid)
            {
                return FAIL;
            }
            return semid;
        }
    } 
    if(FAIL == BinarySemInit(semid))
    {
        printf("init fail\n");
        return FAIL;
    }
    return semid;
}

static int GetSemVal(int sid, int number, int undo)
{
    int sem_val = 0;
    if(-1 == (sem_val = semctl(sid, 0, GETVAL, 0)))
    {
        return FAIL;
    }
    fprintf(stdout, "semaphore with id %d value is: %d\n", sid, sem_val);
    (void)number;
    (void)undo;
    return SUCCESS;
}

static int DecreaseSemVal(int sid, int number, int undo)
{
    struct sembuf sops[1] = {0};
    sops[0].sem_num = 0;
    sops[0].sem_op = -number;
    if(undo)
    {
        sops[0].sem_flg = SEM_UNDO; 
    }
    
    return semop(sid, sops, NUM_OF_SEM_IN_SET);
}

static int IncreaseSemVal(int sid, int number ,int undo)
{
    struct sembuf sops[1] = {0};
    sops[0].sem_num = 0;
    sops[0].sem_op = number;
    if(undo)
    {
        sops[0].sem_flg = SEM_UNDO; 
    }
    
    return semop(sid, sops, NUM_OF_SEM_IN_SET);
}

static void GetArgs(char *c, int *number, int *undo_flag)
{
    char line[50] = {'\0'};
    if(NULL == fgets(line, 49, stdin))
    {
        *c = 'E';
        return;
    }
    *c = *line;
    if('D' == *c || 'I' == *c )
    {
        *number = atoi(line + 2);

        if(NULL != strstr(line + 3, "undo"))
        {
            *undo_flag = 1;
        }
    }
}

static int Exit(int sid, int number ,int undo)
{
    (void)sid;
    (void)number;
    (void)undo;
    return FAIL;
}

static int BinarySemInit(int semid)
{
    union semun argument;
    unsigned short values[1];
    values[0] = 1;
    argument.array = values;  
    return semctl(semid, 0, SETALL, argument);
}

static int InvalidInput(int sid, int number, int undo)
{
    printf("not a valid option");
    (void)sid;
    (void)number;
    (void)undo;
    return SUCCESS;
}

static void InitOpLut(SemOperation *operation_lut)
{
    size_t i = 0; 
    assert(NULL != operation_lut);

    for(i = 0; i < 256; ++i)
    {
        operation_lut[i] = InvalidInput;
    }

    operation_lut['D'] = DecreaseSemVal;
    operation_lut['I'] = IncreaseSemVal;
    operation_lut['V'] = GetSemVal;
    operation_lut['X'] = Exit;
}




