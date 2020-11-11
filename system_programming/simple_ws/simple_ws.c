#include <sys/wait.h>/*wait*/
#include <stdlib.h>/*exit*/
#include <unistd.h>/*fork*/
#include <stdio.h>/*printf*/


int main(int argc, char *argv[])
{
    pid_t cpid = 0, w = 0;
    int wstatus = 0;

    while(1)
    {
        cpid = fork();
        if (-1 == cpid ) 
        {
            printf("fork error");
            exit(EXIT_FAILURE);
        }
        if (0 == cpid) 
        {            /* Code executed by child */
            execv("/home/rotemkadosh27/git/system_programming/simple_ws/dummy.out",argv);
            
            printf("exec error\n");
            exit(EXIT_FAILURE);
        } 
        else 
        {                    /* Code executed by parent */
            w = wait(&wstatus);
            if (-1 == w) 
            {
                printf("wait error\n");
                exit(EXIT_FAILURE);
            }
            if (WIFEXITED(wstatus))
            {
                printf("exited, status=%d\n", WEXITSTATUS(wstatus));
            } 
        }
    } 
    exit(EXIT_SUCCESS);
}























