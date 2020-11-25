#ifndef __SYSVSEMAPHORE_H__
#define __SYSVSEMAPHORE_H__

int CreateSemaphore(const char *proj_id_str);

int DecreaseSemValue(int sem_id, short num, short flag);

int IncreaseSemValue(int sem_id, short num, short flag);

int CloseSem(int sid);

#endif