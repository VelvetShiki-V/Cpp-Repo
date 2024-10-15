#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<assert.h>
#include<string.h>
#define NUM 1024

typedef struct myfile {
    int fd;
    char buf[NUM];
    int end;
}MyFILE;

MyFILE* Myfopen(const char* path, const char* mode) {
    assert(path && mode);
    MyFILE* fp = NULL;
    if(strcmp(mode, "r") == 0);
    else if(strcmp(mode, "w") == 0) {
        int fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
        if(fd >= 0) {
            fp = (MyFILE*)malloc(sizeof(MyFILE));
            memset(fp, 0, sizeof(MyFILE));
            fp->fd = fd;
        }
    }
    else if(strcmp(mode, "a"));
    else assert(0);
    return fp;
}

void Myfputs(const char* str, MyFILE* fp) {
    assert(str && fp);
    strcpy(fp->buf+fp->end, str);
    fp->end += strlen(str);
    if(fp->fd == 0);
    else if(fp->fd == 1) {
        if(fp->buf[fp->end - 1] == '\n') {
            fprintf(stderr, "buf->fd:%s", fp->buf);
            write(fp->fd, fp->buf, fp->end);
            fp->end = 0;
        }
    }
}

void Myfflush(MyFILE* fp) {
    assert(fp);
    if(fp->end != 0) {
        write(fp->fd, fp->buf, fp->end);
        syncfs(fp->fd);
        fp->end = 0;
    }
}

void Myfclose(MyFILE* fp) {
    assert(fp);
    Myfflush(fp);
    close(fp->fd);
    free(fp);
}

int main() {
    close(1);
    MyFILE* fp = Myfopen("test_log.txt", "w");
    if(fp == NULL) {
        perror("log open");
        return -1;
    }
    Myfputs("test1", fp);
    sleep(1);
    Myfputs("test2\n", fp);
    sleep(1);
    Myfputs("test3", fp);
    sleep(1);
    Myfputs("test4\n", fp);
    sleep(1);
    Myfclose(fp);
    return 0;
}
