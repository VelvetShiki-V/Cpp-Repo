#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    pid_t id = fork();
    if(id < 0)
    {
        perror("fork failed");
        exit(1);           // 标识fork失败，进程以-1返回，结果不正确
    }
    else if(id == 0)
    {
        int count = 5;
        while(count)
        {
            printf("%d, child proc, pid: %d, ppid: %d\n", count, getpid(), getppid());
            sleep(1);
            count--;
        }
        exit(100);
    }
    else
    {
        sleep(7);
        printf("parent proc, pid: %d, ppid: %d\n", getpid(), getppid());
        int status = 0;
        //pid_t ret = wait(NULL);     // 阻塞式等待
        pid_t ret = waitpid(id, &status, 0);
        if(ret > 0)
        {
            printf("等待子进程成功，ret = %d, status = %d\n", ret, ((status) >> 8)&(0xFF));
        }
    }
    exit(3);
}
