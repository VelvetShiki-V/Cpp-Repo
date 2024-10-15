#ifndef __EPOLLSERVER_HPP
#define __EPOLLSERVER_HPP
#pragma once
#include <iostream>
#include "log.hpp"
#include "sock.hpp"
#include "epoll.hpp"
#include <functional>
#include <cassert>
#include <string>
#define SIZE 1024

namespace epoll_server{
    static const int default_port = 8080;
    static const int default_handle = 100;
    typedef std::function<void(std::string)> func_t;

    class EpollServer {
    public:
        EpollServer(func_t regist_func, const int& port = default_port, const int& max_handle = default_handle) 
        :_port(port)
        ,_max_reps(max_handle)
        ,_handler(regist_func)
        {
            // 1. 初始化服务器
            _listen_sock = Sock::socket_create();
            Sock::socket_bind(_listen_sock, _port);
            Sock::service_listen(_listen_sock);
            logMessage(NORMAL, "service init done, listen_sock: %d, listening...", _listen_sock);
            // 2. 初始化epoll，将listen套接字放入epoll中检测IO事件
            _epoll_sock = Epoll::ep_create();
            if(Epoll::ep_ctl(_epoll_sock, _listen_sock, EPOLL_CTL_ADD, EPOLLIN) < 0) exit(-1);
            // 3. 初始化IO就绪结构体数组（准备从内核就绪队列中获取资源）
            reps = new epoll_event[_max_reps];
            logMessage(NORMAL, "epoll init done, epoll sock: %d, listen_sock insert into epoll: %d", _epoll_sock);
        }

        void service_each_loop(int timeout) {
            int n = Epoll::ep_wait(_epoll_sock, reps, _max_reps, timeout);
            switch(n) {
                case -1: {
                    logMessage(ERROR, "revents obtained from queue failed-%d:%s", errno, strerror(errno));
                    break;
                }
                case 0: {
                    logMessage(WARNING, "timeout");
                    break;
                }
                default: {
                    logMessage(DEBUG, "%d fds and events are ready to handle", n);
                    eventsHandler(n);
                    break;
                }
            }
        }

        void run() {
            while(true) {
                service_each_loop(1000);
            }
        }
        
        // fd就绪，进行IO处理
        void eventsHandler(int n) {
            assert(n > 0);
            for(int i = 0; i < n; ++i) {        // 明确仅获取到n个就绪fd和event结构体，仅遍历n次
                int fd = reps[i].data.fd;
                uint32_t revents = reps[i].events;
                // 处理只读IO事件
                if(revents & EPOLLIN) {
                    if(fd == _listen_sock) acceptor();
                    else receiver(fd);
                }
            }
        }

        // 获取新连接
        void acceptor() {
            // 获取客户端连接的ip和端口号，并创建服务套接字
            string ip;
            uint16_t port;
            int service_sock = Sock::client_accept(_listen_sock, &ip, &port);
            // 将套接字插入epoll红黑树中
            if(Epoll::ep_ctl(_epoll_sock, service_sock, EPOLL_CTL_ADD, EPOLLIN) < 0) {
                logMessage(ERROR, "%d add-to epoll failed", service_sock);
            }
            else logMessage(DEBUG, "get a new link from client, service_sock: %d", service_sock);
        }

        // 进行只读IO事件
        void receiver(int readfd) {
            char buf[SIZE];
            ssize_t n = recv(readfd, buf, sizeof buf - 1, 0);       // 0为阻塞读取
            if(n < 0) {
                logMessage(ERROR, "fd: %d read failed-%d:%s", readfd, errno, strerror(errno));
                // 读取失败，先去epoll底层结点（红黑树），再关闭
                Epoll::ep_ctl(_epoll_sock, readfd, EPOLL_CTL_DEL, 0);
                close(readfd);
            }
            else if(n == 0) {
                logMessage(ERROR, "fd: %d closed-%d:%s", readfd, errno, strerror(errno));
                // 读取失败，先去epoll底层结点（红黑树），再关闭
                Epoll::ep_ctl(_epoll_sock, readfd, EPOLL_CTL_DEL, 0);
                close(readfd);
            }
            else {
                logMessage(DEBUG, "fd: %d data obtained");
                buf[n] = 0;
                _handler(buf);
            }
        }

        ~EpollServer() {
            if(_listen_sock >= 0) close(_listen_sock);
            if(_epoll_sock >= 0) close(_epoll_sock);
            if(reps) delete[] reps;
        }

    private:
        int _listen_sock;
        uint16_t _port;
        int _epoll_sock;        // epoll模型套接字
        int _max_reps;          // 结构体最大个数
        epoll_event* reps;      // 获取就绪数据结构体数组
        func_t _handler;        // 注册的数据处理方法（当前只读）  
    };
}

#endif