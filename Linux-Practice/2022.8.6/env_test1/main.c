#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[], char *env[])
{
    char* envir = getenv("shiki");
    if(envir)
    {
        printf("pid = %d, ppid = %d\n", getpid(), getppid());
        printf("%s\n", envir);
    }
    //while(1)
    //{
    //    sleep(1);
    //}
    return 0;
}
