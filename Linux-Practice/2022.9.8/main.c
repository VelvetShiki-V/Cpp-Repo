#include<stdio.h>
#include<unistd.h>

int global = 10;

int main()
{
    pid_t id = fork();
    if(id == 0)
    {
        //child process, ppid is father proc
        int count = 1;
        while(1)
        {
             printf("Child proc, pid = %d, ppid = %d, val = %d, add = %p\n", getpid(), getppid(), global, &global);
             count++;
             if(count == 5)
             {
                 global = 20;
                 printf("child proc's global is reset to 20 successfully\n");
             }
             sleep(1);
        }
    }
    else
    {
        //father process, ppid is bash
        while(1)
        {
             printf("Father proc, pid = %d, ppid = %d, val = %d, add = %p\n", getpid(), getppid(), global, &global);
             sleep(1);
        }
    }
    return 0;
}
