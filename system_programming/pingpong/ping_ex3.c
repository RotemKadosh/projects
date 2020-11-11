#include <stdio.h>  /*printf*/
#include <sys/types.h> /*pid_t*/
#include <unistd.h> /*execv*/
#include <stdlib.h>  /*system*/
#include <signal.h> /*sigaction*/
#define FAIL (-1)
#define TRUE (1)


static pid_t pong_id = 0;


void Usr2SigHand(int sig, siginfo_t *inf, void *ucontext)
{
    pong_id = inf->si_pid;
    write(STDOUT_FILENO, "ping ", 6);
    
}

int main(int argc, char *argv[])
{
    struct sigaction usr2hand;
    usr2hand.sa_sigaction = Usr2SigHand;
    usr2hand.sa_flags = SA_NODEFER | SA_SIGINFO;
    if(FAIL == sigaction(SIGUSR2, &usr2hand, NULL))
    {
        printf("sigaction fail\n");
        exit(FAIL);
    }
    
    sleep(30);
    while(TRUE)
    {
        if(FAIL == kill(pong_id, SIGUSR1))
        {
            printf("kill fail\n");
            exit(FAIL);  
        }
        pause();
    }
    return 0; 
}
 