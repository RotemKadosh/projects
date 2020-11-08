#include "../utils/test.h"
#include <stdio.h>
#include "kt.h"

static void PrintSol(size_t arr[], size_t size)
{
    size_t i = 0;
    for(i = 0; i < size -1; ++ i)
    {
        printf("%ld ->", arr[i]);
        if(i % 8 == 0)
        {
            printf("\n");
        }
    }
    printf("%ld\n", arr[i]);
}


static test_status_t TestAlgorithm(void)
{
    size_t board = 0;
    size_t pos = 1;
    size_t sol[64] = {0};
    int ans = -1;
    ans = KTSolve(pos, board, sol);
    PrintSol(sol, 64);
    printf("%s",ans == 1 ? "SUCCESS": "FAIL");
    return PASSED;
}

int main()
{
    RUNTEST(TestAlgorithm);
    return 0;
}

