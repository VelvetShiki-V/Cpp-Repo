#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main() {
    umask(0);
    //int ret = open("file2.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);    // 0为8进制，666为文件权限
    //int ret = open("file2.txt", O_WRONLY|O_CREAT|O_APPEND, 0666);    // 0为8进制，666为文件权限
    int ret = open("file2.txt", O_RDONLY, 0666);    // 0为8进制，666为文件权限
    if(ret < 0) {
        perror("file2 open status");
        return(1);
    }
    else {
        printf("file2 open successfully, ret = %d\n", ret);
        char buffer[128];
        // 读取文件
        // 须手动设置以'\0'结尾,因为read仅读取有效字符个数ssize_t
        //ssize_t s = read(0, buffer, sizeof(buffer));
        //if(s > 0) {
        //    printf("read success\n");
        //    buffer[5] = '\0';
        //    printf("%s", buffer);
        
        // 测试1
        //}
        memset(buffer, '\0', sizeof(buffer));
        read(ret, buffer, sizeof(buffer));
        printf("%s\n", buffer);
        // 写入文件
        //const char* str = "\0";
        //const char* str = "second\n";
        //write(ret, str, strlen(str));
    }
    // 关闭文件
    close(ret);
    return 0;
}
