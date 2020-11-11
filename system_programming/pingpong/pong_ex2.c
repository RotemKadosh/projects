#include <stdio.h>  /*printf*/
#include <sys/types.h> /*pid_t*/
#include <unistd.h> /*execv*/
#include <stdlib.h>  /*system*/
#include <signal.h> /*sigacftion*/

#define FAIL (-1)
#define TRUE (1)

void Usr1SigHand(int sig)
{
    write(STDOUT_FILENO, "pong\n", 6);
}

int main(int argc, char *argv[])
{  
    pid_t ppid = 0;
    struct sigaction usr1hand;

    usr1hand.sa_handler = Usr1SigHand;
    usr1hand.sa_flags = SA_NODEFER;

    
    if(FAIL == sigaction(SIGUSR1, &usr1hand, NULL))
    {
        printf("sigaction fail\n");
        exit(FAIL);
    }
    
    ppid = getppid();

    while(TRUE)
    {
        if(FAIL == kill(ppid, SIGUSR2))
        {
            printf("kill fail\n");
            exit(FAIL);
        } 
        pause();
    }
    return 0;

}