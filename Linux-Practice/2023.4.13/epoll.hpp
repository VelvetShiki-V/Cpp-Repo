#ifndef __EPOLL_HPP
#define __EPOLL_HPP
#pragma once
#include <sys/epoll.h>
#include <iostream>
#include "log.hpp"
#include <cerrno>

class Epoll{
public:
    // 1. 创建epoll模型
    static int ep_create() {
        int poll_sock = epoll_create(_epoll_size);
        if(poll_sock < 0) {
            logMessage(FATAL, "epoll create-%d:%s", errno, strerror(errno));
            exit(4);
        }
        return poll_sock;
    }
    // 2. 对epoll模型底层红黑树进行结点增删改操作
    static int ep_ctl(int epoll_sock, int fd, int ep_act, uint32_t event) {
        epoll_event events;
        events.data.fd = fd;
        events.events = event;
        int flag = epoll_ctl(epoll_sock, ep_act, fd, &events);
        if(flag < 0) {
            logMessage(ERROR, "epoll conduct: %d to fd: %d failed-%d:%s", ep_act, fd, errno, strerror(errno));
        }
        return flag;
    }
    // 3. 对存入其中的文件描述符进行监视等待（有IO会检测事件发生一致性，再推入就绪队列中）
    static int ep_wait(int epoll_sock, epoll_event* reps, int reps_nums, int timeout) {
        return epoll_wait(epoll_sock, reps, reps_nums, timeout);
    }
private:
    static const int _epoll_size = 256;
};

#endif