#include <stdlib.h> /*system*/
#include <unistd.h> /*exit*/
#include <stdio.h> /*printf*/


int main(int argc, char *argv[])
{
    int status = 0;
   
   /* while(1)
    {*/
        status = system("ps");
        if (-1 == status ) 
        {
            printf("child creation error");
            exit(EXIT_FAILURE);
        }
        if (127 == status) 
        {            
            printf("child could not exec error\n");
            exit(EXIT_FAILURE);
        } 
     
    exit(EXIT_SUCCESS);
}