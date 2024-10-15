#ifndef __SHMCOMM_H_
#define __SHMCOMM_H_
#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>
using namespace std;

#define DEBUG 0              // 日志记录等级
#define NOTICE 1
#define WARNING 2
#define ERROR 3
#define PJID 0x01           // 项目ID（随机）
#define SHM_SIZE 4096       // 共享内存大小（以页PAGE为单位，每页4096bytes）
#define MODE 0666           // 创建共享内存默认权限
#define FIFO_PATH "./named_pipe"
#define READ O_RDONLY
#define WRITE O_WRONLY
const char* PATH = ".";     // 项目路径


// 日志记录信息
const string msg[] = {
    "DEBUG",
    "NOTICE",
    "WARNING",
    "ERROR"
};
// 输出日志信息
ostream& Log(const string& s, int level) {
    cout << " | " << (unsigned)time(nullptr) << " | " << s <<  " | " << msg[level] << " | ";
    return cout; 
}
// key值转十六进制
string hex_trans(key_t key) {
    char buf[32];
    snprintf(buf, sizeof buf, "0x%x", key);
    return buf;
}

// 命名管道访问控制类
class Init{
    public:
    Init() {
        umask(0);
        int ret = mkfifo(FIFO_PATH, MODE);      // 创建命名管道，并根据该管道控制共享区访问控制
        assert(ret == 0);
        Log("命名管道已创建", DEBUG) << endl;
        (void)ret;
    }
    ~Init() {                                   // 管道生命周期随进程，进程结束管道也删除
        unlink(FIFO_PATH);
        Log("命名管道已删除", DEBUG) << endl;
    }
};

int Open_pipe(const char* path, int mode) {  // 让通信进程双方与管道建立关联
    int fd = open(path, mode);
    assert(fd != -1);
    Log("命名管道打开成功", DEBUG) << endl;
    return fd;
}

void Wait(int fd) {                             // 服务器读端等待客户端写入，等待环形
    size_t output = 0;
    Log("服务器等待中...", NOTICE) << endl;
    ssize_t s = read(fd, &output, sizeof output);
    assert(s == sizeof output);
    (void)s;
}

void Waken(int fd) {                            // 用户端向共享区内写入数据，向服务器端发出唤醒信号
    size_t input = 1;
    Log("用户端写入中...", NOTICE) << endl;
    ssize_t s = write(fd, &input, sizeof input);
    assert(s == sizeof input);
    (void)s;
}

void Close_pipe(int fd) {       // 管道去关联
    close(fd);
}
#endif