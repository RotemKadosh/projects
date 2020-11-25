#include <stdlib.h>/*size_t, atoi*/
#include <stdio.h>/*printf */
#include <string.h>/*strcmp' strtok*/
#include <sys/sem.h>/*ftok,semget, semctl , semop*/
#include <errno.h>/*errno*/
#include <assert.h>/*assert*/
#include "sysvsemaphore.h"

#define FAIL (-1)
#define SUCCESS (0)

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int OpenFile(void)
{
    FILE *file = NULL;
    char *path = "semaphore_file";
    int stat = FAIL;
    file = fopen(path, "w");
    if(NULL != file)
    {
        if(EOF != fclose(file))
        {
            stat = SUCCESS;
        }
    }
    return stat;
}

int CreateSemaphore(const char *proj_id_str)
{
    key_t sem_key = 0;
    int sem_id = 0, proj_id = 0;
    char *path = "semaphore_file";
    union semun argument = {0};
    unsigned short values[1] = {1};
    argument.array = values;

    assert(NULL != proj_id_str);

    if(FAIL == OpenFile())
    {
        return FAIL;
    }

    proj_id = atoi(proj_id_str);
    sem_key = ftok(path, proj_id);
    if(FAIL != sem_key)
    {
        sem_id = semget(sem_key, 1, IPC_EXCL | IPC_CREAT | 0666);
        if(FAIL != sem_id)
        {
            if(FAIL == semctl(sem_id, 0, SETALL, argument))
            {
                semctl(sem_id, 0, IPC_RMID, 0);
                return FAIL;
            }      
        }
        else
        {
            if(EEXIST == errno)
            {
                sem_id = semget(sem_key, 1, 0);
                if (FAIL == sem_id)
                {
                    return FAIL;
                }  
            }
        }  
    }
    return sem_id;
}



int DecreaseSemValue(int sem_id, short num, short flag)
{
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = -num;
    sops.sem_flg = flag;
    
    return semop(sem_id, &sops, 1);
}

int IncreaseSemValue(int sem_id, short num, short flag)
{
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = num;
    sops.sem_flg = flag;

    return semop(sem_id, &sops, 1);   

}

int CloseSem(int sem_id)
{
    if(FAIL == semctl(sem_id, 0, IPC_RMID, 0))
    {
        return FAIL;
    }
    return SUCCESS;
}
    