#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#define NUM 20
//const char* myfile = "/home/shiki/linux_-practice/2022.9.27/test";    // 绝对路径的环境变量找test程序
const char* myfile = "./test";      // 相对路径的环境变量找test程序

int main() {
    char* const _env[NUM] = {                 // 定义环境变量
        (char*)"myenv=this is a test",        // 不能打空格！
        NULL
    };
    pid_t id = fork();
    if(id == 0) {
        printf("child process begin\n");        
        //execl("/usr/bin/ls", "ls", "-l", "-a", "--color=auto", NULL);
        //execl("ls", "ls", "-l", "-a", "--color=auto", NULL);
        execle(myfile, "test", "-c", NULL, _env);
        printf("child process end\n");        
        exit(-1);
    }
    else {
        printf("parent process begin\n");
        int status = 0;
        pid_t ret = 0;
        ret = waitpid(-1, &status, 0);
        if(ret > 0) {
            printf("wait successfully, exit code is %d\n", WEXITSTATUS(status));
        }
    }
    return 0;
}
