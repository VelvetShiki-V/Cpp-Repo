#ifndef __SHMCOMM_H_
#define __SHMCOMM_H_
#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
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
#endif