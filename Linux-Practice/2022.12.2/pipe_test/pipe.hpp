#ifndef __PIPE_HPP
#define __PIPE_HPP
#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
using namespace std;

const string PATH = "./mypipe";     // 管道文件具有系统路径，位于当前目录下
#define SIZE 1024       // 可以一次性输入管道的数据大小(标准512字节，linux下最大4096字节)
#define MODE 0666       // 默认创建的命名管道文件权限(rw-rw-r)
#define DEBUG 0         // 用于记录日志的信息
#define NOTICE 1
#define WARNING 2
#define ERROR 3
#define CHILDNUMS 3     // 服务器端创建子进程数目

const string msg[] = {  // 日志提示字符串数组
    "DEBUG",
    "NOTICE",
    "WARNING",
    "ERROR"
};

ostream& Log(const string& s, int sig) {        // Log函数用于打印提示操作过程中的信息
    cout << " | " << (unsigned)time(nullptr) << " | " << msg[sig] << " | " << s;
    return cout;
}

#endif