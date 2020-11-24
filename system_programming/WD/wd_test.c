#include <stdio.h>
#include <unistd.h>
#include "wd.h"
#include "../../ds/utils/test.h"



int main(int argc, char **argv)
{
    
    int arr [10] = {0};
    size_t num = 9999999999;
    printf("I Am the Main Process, I am alive, id : %d\n", getpid());
    StartWd(argv);
    while(num > 0)
    {
        --num;
    }
    arr[2] = 5;
    StopWd();


    (void)argc;

    printf("bye\n");
    return 0;
}
