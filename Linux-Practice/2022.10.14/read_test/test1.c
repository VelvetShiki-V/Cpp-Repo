#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

#define NUM 128

int main() {
    //int fd = open("file1.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
    int fd = open("file1.txt", O_RDONLY, 0666);
    if(fd < 0) {
        perror("file1");
        return 1;
    }
    else {
        char buffer[NUM];
        memset(buffer, '\0', sizeof(buffer));
        ssize_t s = read(fd, buffer, sizeof(buffer));
        if(s > 0) {
            printf("读到了%zd个字节\n", s);
            printf("内容：%s", buffer);
        }
    }
    close(fd);
    return 0;
}
