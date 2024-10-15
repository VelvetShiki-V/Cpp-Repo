#ifndef __EPOLL_HPP
#define __EPOLL_HPP
#pragma once
#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include "log.hpp"

class Epoll {
public:
    // 创建epoll模型
    void ep_create() {
        _epfd = epoll_create(_ep_size);     // size无意义参数
        if(_epfd < 0) {
            logMessage(FATAL, "epoll create failed-%d:%s", errno, strerror(errno));
            exit(1);
        }
    }

    // IO只读监视的fd插入epoll控制（默认只读监视）
    bool epoll_add(const int& sockfd) {
        epoll_event ev;
        ev.data.fd = sockfd;
        ev.events = EPOLLIN | EPOLLET;      // 监视的fd对应IO行为只读，且工作模式为ET（仅通知一次数据就绪）
        if(epoll_ctl(_epfd, EPOLL_CTL_ADD, sockfd, &ev) < 0) {
            logMessage(ERROR, "sock: %d added to epoll failed-%d:%s", sockfd, errno, strerror(errno));
            return false;
        }
        return true;
    }

    // 从epoll中移除监视中fd结点
    bool epoll_rmv(const int& sockfd) {
        epoll_event ev;
        ev.data.fd = sockfd;
        if(epoll_ctl(_epfd, EPOLL_CTL_DEL, sockfd, nullptr) < 0) {      // 对IO事件不关心
            logMessage(ERROR, "sock: %d removed failed-%d:%s", sockfd, errno, strerror(errno));
            return false;
        }
        return true;
    }

    // 监视中fd的IO事件等待
    int ep_wait(epoll_event* revs, const int& max_revs) {
        int n = epoll_wait(_epfd, revs, max_revs, _timeout);
        switch(n) {
            case -1: {
                logMessage(ERROR, "sock wait failed-%d:%s", errno, strerror(errno));
                break;
            }
            case 0: {
                // logMessage(WARNING, "sock wait timeout");
                break;
            }
            default: {
                logMessage(DEBUG, "sock wait succ, counts: %d fds are ready to handle", n);
                break;
            }
        }
        return n;
    }

    // 控制epooll监视中的套接字读写权限：传入true打开，false关闭对应权限
    bool ep_ctl(int& sockfd, bool rdctl, bool wrctl) {
        epoll_event ev;
        ev.data.fd = sockfd;
        if(rdctl) ev.events |= EPOLLIN;
        if(wrctl) ev.events |= EPOLLOUT;
        if(epoll_ctl(_epfd, EPOLL_CTL_MOD, ev.data.fd, &ev) < 0) {
            logMessage(ERROR, "sock: %d read/write modify failed", sockfd);
            return true;
        }
        return true;
    }

    int get_epfd() {
        return _epfd;
    }
    
    ~Epoll() {
        if(_epfd >= 0) close(_epfd);
    }
private:
    int _epfd;
    static const int _ep_size = 100;
    static const int _timeout = 1000;
};
#endif