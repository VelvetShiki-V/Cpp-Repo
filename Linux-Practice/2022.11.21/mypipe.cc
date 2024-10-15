#include <iostream>
#include <cstdio>
#include <cstring>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
#define SIZE 1024

int main() {
    // 创建管道
    int pipefd[2] = {0};
    int ret = pipe(pipefd);
    assert(ret != -1);
    (void)ret;

    #ifdef DEBUG
    cout << "pipefd[0]: " << pipefd[0] << endl;
    cout << "pipefd[1]: " << pipefd[1] << endl;
    #endif

    //创建子进程
    int fd = fork();
    assert(fd >= 0);
    if(fd == 0) {
        // child proc
        close(pipefd[1]);       // 关闭子进程对共享管道文件的写端
        char buffer[SIZE];      // 设置将从父进程写入管道文件再读取到子进程的缓冲区
        while(true) {
            //sleep(5);
            ssize_t end = read(pipefd[0], buffer, sizeof(buffer) - 1);      // 读取共享管道文件
            if(end) {
                buffer[end] = 0;
                printf("子进程[%d]从父进程[%d]读取到数据: %s\n", getpid(), getppid(), buffer);
            }
            else {
                cout << "写端关闭，管道没有待读取数据，读端关闭" << endl;
                break;
            }
        }
        exit(0);
    }
    else {
        // parent proc
        close(pipefd[0]);           // 关闭父进程对共享管道文件的读端
        string s = "父进程讯息——";
        int cnt = 0;
        char send_buffer[SIZE];     // 设置父进程将写入共享管道文件的输出缓冲区
        while(true) {
            snprintf(send_buffer, sizeof(send_buffer), "%s%d", s.c_str(), ++cnt);       // 以格式化写入方式将各种数据写入缓冲区
            write(pipefd[1], send_buffer, strlen(send_buffer));     // 再将输出缓冲区数据写入共享管道文件中
            sleep(1);
            cout << cnt << endl;
            if(cnt == 10) {
                cout << "父进程写端关闭" << endl;
                close(pipefd[1]);
                break;
            }
        }
        int ret2 = waitpid(fd, nullptr, 0);     // 当父进程不再有数据写入，且子进程不再有数据读取时，进程等待并关闭描述符，退出
        assert(ret2 > 0);
        (void)ret2;
        close(pipefd[1]);
    }
    return 0;
}
