#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("Child PID is %ld\n", (long) getpid());
    system("ps");
    _exit(127);
    return 0;
}