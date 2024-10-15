#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{
    pid_t ret = fork(); 
    if(ret < 0)
    {
        perror("fork failure\n");
        return -1;
    }
    else if(ret == 0)
    {
       // while(1)
        {
             printf("This is childproc, pid = %d, ppid = %d\n", getpid(), getppid());
             sleep(1);
    //         break;
    //         exit(0);
        }
    }
    else
    {
       //while(1)
        {
             printf("This is parent proc, pid = %d, ppid = %d\n", getpid(), getppid());
             sleep(1);
        }
    }
    // while(1)
    //{
    //     printf("pid = %d, ppid = %d\n", getpid(), getppid());
    //     sleep(1);
    //}
    return 0;
}
