#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("至少带有一个选项\n");
        exit(-1);
    }
    printf("从父进程继承得到的环境变量myenv的值为: %s\n", getenv("myenv"));
    if (strcmp(argv[1], "-a") == 0) {
        printf("这是选项a\n");
    }
    else if (strcmp(argv[1], "-b") == 0) {
        printf("这是选项b\n");
    }
    else {
        printf("其他未定义选项\n");
    }
}
