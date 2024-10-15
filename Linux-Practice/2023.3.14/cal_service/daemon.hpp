#ifndef __DAEMON_HPP
#define __DAEMON_HPP
#pragma once
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include "log.hpp"
#define FILE_REDIRECT "/dev/null"

namespace ProcGuard {
    void Daemon() {
        // 1. 忽略子进程退出或通信管道关闭（客户端退出）情况
        signal(SIGPIPE, SIG_IGN);
        signal(SIGCHLD, SIG_IGN);

        // 2. 进程退出当前会话组，自成一组
        pid_t id = fork();
        if(id > 0) exit(5);
        if(id < 0) {
            logMessage(FATAL, "fork fail--%d:%s", errno, strerror(errno));
            exit(1);
        }
        pid_t sid = setsid();
        if(sid < 0) {
            logMessage(FATAL, "new session create fail--%d:%s", errno, strerror(errno));
            exit(2);
        }
        logMessage(NORMAL, "sid: %d", sid);

        // 3. 标准输入输出错误重定向（防阻塞）
        int fd = open(FILE_REDIRECT, O_RDONLY | O_WRONLY);
        if(fd > 0) {
            dup2(0, fd);        // 
            dup2(1, fd);
            dup2(2, fd);
            close(fd);
        }
    }       
}
#endif