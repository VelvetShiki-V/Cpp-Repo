#include<stdio.h>
#include<stdlib.h>
int main() {
    printf("获取到的自定义环境变量myenv:%s\n", getenv("myenv"));
    printf("主机环境变量shikienv:%s\n", getenv("shikienv"));
    return 0;
}
