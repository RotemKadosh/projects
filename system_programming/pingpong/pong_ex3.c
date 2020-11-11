#include <stdio.h>  /*printf*/
#include <sys/types.h> /*pid_t*/
#include <unistd.h> /*execv*/
#include <sys/wait.h> /*wait*/
#include <stdlib.h>  /*system*/
#include <signal.h> 


#define FAIL (-1)
#define TRUE (1)

void Usr1SigHand(int sig, siginfo_t *inf, void *ucontext)
{
    write(STDOUT_FILENO, "pong\n", 6);
}

int main(int argc, char *argv[])
{
    char *p_id = argv[1];
    pid_t ping_id = 0;
    
    struct sigaction usr1hand;
    usr1hand.sa_sigaction = Usr1SigHand;
    usr1hand.sa_flags = SA_NODEFER | SA_SIGINFO ;

    ping_id = (pid_t )atoi(p_id);

    if(FAIL == sigaction(SIGUSR1, &usr1hand, NULL))
    {
        printf("sigaction fail\n");
        exit(FAIL);
    }
    if(FAIL == kill(ping_id, SIGUSR2))
    {
        printf("kill fail\n");
        exit(FAIL);
    }
    while(TRUE)
    {
        pause();
        if(FAIL == kill(ping_id, SIGUSR2))
        {
            printf("kill fail\n");
            exit(FAIL);
        }

    }
    return 0;

}