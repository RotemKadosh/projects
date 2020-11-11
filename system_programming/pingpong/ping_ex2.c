#include <stdio.h>  /*printf*/
#include <sys/types.h> /*pid_t*/
#include <unistd.h> /*execv*/
#include <stdlib.h>  /*system*/
#include <signal.h> /*sigaction*/

#define FAIL (-1)
#define TRUE (1)


void Usr2SigHand(int sig)
{
    write(STDOUT_FILENO, "ping ", 6);
}

int main(int argc, char *argv[])
{
    struct sigaction usr2hand;
    
    pid_t pid = fork();
    usr2hand.sa_handler = Usr2SigHand;
    usr2hand.sa_flags = SA_NODEFER;
    

    if(0 > pid)
    {
        printf("fork fail\n");
        exit(FAIL);
    }
    if(0 == pid)
    {
        execv("/home/rotemkadosh27/git/system_programming/pingpong/pong.out", argv);
    }
    else
    {
        if(FAIL == sigaction(SIGUSR2, &usr2hand, NULL))
        {
            printf("sigaction fail\n");
            exit(FAIL);
        }
        sleep(10);

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