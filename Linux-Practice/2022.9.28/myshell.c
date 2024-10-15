#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#define NUM 1024
#define SIZE 32
#define SEP " "

char g_cmd_line[NUM];
char* g_argv[SIZE];
char g_myenv[SIZE];

int main() {
    while(1) {
        printf("[supershiki@localhost myshell]# ");
        fflush(stdout);
        memset(g_cmd_line, '\0', sizeof g_cmd_line);
        if(fgets(g_cmd_line, sizeof g_cmd_line, stdin) == NULL) {
            continue;
        }
        g_cmd_line[strlen(g_cmd_line) - 1] = '\0';
        //printf("%s\n", g_cmd_line); 测试获取输入的指令
        g_argv[0] = strtok(g_cmd_line, SEP);
        int index = 1;
        if(strcmp("ls", g_argv[1]) == 0) {
            g_argv[index++] = (char*)"--color=auto";
        }
        if(strcmp("ll", g_argv[0]) == 0) {
            g_argv[0] = (char*)"ls";
            g_argv[index++] = (char*)"-l";
            g_argv[index++] =(char*)"--color=auto";
        }
        while(g_argv[index++] = strtok(NULL, SEP));
        // 通过export指令获取环境变量
        if(strcmp("export", g_argv[0]) == 0 && g_argv[1] != NULL) {
            strcpy(g_myenv, g_argv[1]);     // 必须进行环境变量值拷贝，否则该命令结束，等待下条命令执行时，指令行g_argv将被清空置\0
            int ret = putenv(g_myenv);
            if(ret == 0)printf("%s export success\n", g_myenv);

            continue;
        }
        //for(index = 0; g_argv[index]; index++) {
        //    printf("%s\n", g_argv[index]);
        //}
        //通过cd指令执行shell对父进程自身的TODO内置指令执行，更改自己当前目录
        if(strcmp("cd", g_argv[0]) == 0) {
            if(g_argv[1] != NULL) {
                chdir(g_argv[1]);
            }
            continue;
        }
        pid_t id = fork();
        if(id < 0) {
            printf("创建子进程失败，程序退出\n");
            exit(-1);
        }
        else if(id == 0) {
            // 环境变量具有全局性，观察是否在子进程中也有效
            printf("父进程创建的环境变量myval:%s\n", g_myenv);
            execvp(g_argv[0], g_argv);
            exit(-2);
        }
        else {
            // parent proc
            int status = 0;
            pid_t ret = waitpid(id, &status, 0);
            if(ret < 0) {
                printf("等待子进程失败，退出码:%d\n", WEXITSTATUS(status));
            }
            else if(ret > 0) {
                printf("等待子进程成功，退出码:%d\n", WEXITSTATUS(status));
            }
        }
    }
    return 0;
}
