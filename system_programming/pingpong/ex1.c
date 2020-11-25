#include <stdio.h>  /*printf*/
#include <sys/types.h> /*pid_t*/
#include <unistd.h> /*execv*/
#include <stdlib.h>  /*system*/
#include <signal.h> /*sigaction*/

#define FAIL (-1)
#define TRUE (1)
int kill(pid_t pid, int sig); 



void Usr1SigHand(int sig)
{
    write(STDOUT_FILENO, "ping ", 6);
}


void Usr2SigHand(int sig)
{
    write(STDOUT_FILENO, "pong\n", 6);

}

int main(int argc, char *argv[])
{
    struct sigaction usr2hand, usr1hand;
    
    pid_t pid = fork();
    pid_t ppid = 0;
    usr2hand.sa_handler= Usr2SigHand;
    usr2hand.sa_flags = SA_NODEFER;

    usr1hand.sa_handler = Usr1SigHand;
    usr1hand.sa_flags = SA_NODEFER;


    if(0 > pid)
    {
        printf("fork fail\n");
        exit(FAIL);
    }
    if(0 == pid)
    {
        ppid = getppid();
        if(FAIL == sigaction(SIGUSR1, &usr1hand, NULL))
        {
            printf("sigaction fail\n");
        }
        while(TRUE)
        {
            pause();
            if(FAIL == kill(ppid, SIGUSR2))
            {
                printf("kill fail\n");
                exit(FAIL);
            }
        }
    }
    else
    {
        if(FAIL == sigaction(SIGUSR2, &usr2hand, NULL))
        {
            printf("sigaction fail\n");
        }
        sleep(5);
        while (TRUE)
        {
            if(FAIL == kill(pid, SIGUSR1))
            {
                printf("kill fail\n");
                exit(FAIL);
            }
            pause();
        }
        
    }
   return 0; 
}
