#ifndef __SELECTSERVER_HPP
#define __SELECTSERVER_HPP
#include <iostream>
#include "sock.hpp"
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
using std::string;
#define SIZE 1024
#define FD_NULL -1

class selectServer{
public:
    selectServer(const uint16_t& port = 8080) {
        listen_sock = m_sock.socket_create();       // 连接三板斧
        m_sock.server_bind(listen_sock, "", port);
        m_sock.server_listen(listen_sock);
        pfds = new struct pollfd[max_fds];
        // 初始化结构体数组pfds，其中每个成员为pollfd，每个pollfd包含三个属性：fd, events, revents
        for(int i = 0; i < max_fds; ++i) {
            pfds[i].fd = FD_NULL;                   // 初始化每个fd置-1
            pfds[i].events = pfds[i].revents = 0;   // 初始化预期检测事件和检测响应事件置0
        }
        // 初始化将listen_sock置入pollfd中
        pfds[0].fd = listen_sock;       // 套接字插入与结构体位置无关，哪里FD_NULL插哪即可
        pfds[0].events = POLLIN;        // 读事件POLLIN，写事件POLLOUT，优先级读取时间POLLPRI...
        logMessage(DEBUG, "server init done, listen_sock: %d, listening...", listen_sock);
    }
    ~selectServer() {
        if(listen_sock >= 0) close(listen_sock);
        if(pfds) delete[] pfds;
    }
    void run() {
        while(true) {
            // 进行倒计时式阻塞式监视等待+通知
            int fds = poll(pfds, max_fds, m_timeout);       // 每次循环进入，timeout会重置，规定2000ms一次IO检测
            // int fds = poll(pfds, max_fds, m_timeout);  
            switch(fds) {
                case 0: {
                    logMessage(ERROR, "fds is unavailable");
                    break;
                }
                case -1: {
                    logMessage(ERROR, "poll error-%d:%s", errno, strerror(errno));
                    break;
                }
                default: {
                    logMessage(DEBUG, "poll success, count: %d fds are ready to handle", fds);
                    handler();      // 监视+等待检测成功，调用对应方法处理客户端IO连接接入
                    break;
                }
            }
        }
    }

    void handler() {
        // 遍历结构体数组，过滤FD_NULL结构体，当fd对应为只读时间且具有检测响应事件时，才会进入处理
        for(int i = 0; i < max_fds; ++i) {
            if(pfds[i].fd == FD_NULL) continue;
            if(pfds[i].revents & POLLIN) {
                if(pfds[i].fd == listen_sock) accepter();
                else receiver(i);
            }
        }
    }

    // 内核态检测IO行为是listen_sock资源就绪，准备accept获取客户端连接
    void accepter() {
        // 1. 接收新的客户端连接，获取ip和port，并开辟新的服务套接字准备接收数据读取
        string client_ip;
        uint16_t client_port;
        int service_sock = m_sock.client_accept(listen_sock, &client_ip, &client_port);
        if(service_sock < 0) {
            logMessage(ERROR, "accept-%d:%s", errno, strerror(errno));
        }
        logMessage(DEBUG, "accept ip[%s], port[%d] done, service_sock: %d", client_ip.c_str(), client_port, service_sock);
        int pos = 1;
        for(pos; pos < max_fds; ++pos) {
            if(pfds[pos].fd == FD_NULL) break;
        }
        if(pos == max_fds) {
            logMessage(ERROR, "poll is full, connection obtained fail");
        }
        else {
            pfds[pos].fd = service_sock;
            pfds[pos].events = POLLIN;
        }
    }
    
    // 内核态检测IO行为是service_sock缓冲区资源就绪，准备recv拷贝数据
    void receiver(const int& pos) {
        // 1. 定义用户态缓冲区，接收缓冲区资源拷贝
        char buf[SIZE];
        ssize_t n = recv(pfds[pos].fd, buf, sizeof buf - 1, 0);
        // 2. 差错处理，读取失败或对端关闭，将套接字关闭并从poll结构体数组pfds中去除，清空events
        if(n < 0) {
            logMessage(ERROR, "data receive fail-%d:%s", errno, strerror(errno));
            close(pfds[pos].fd);
            pfds[pos].fd = FD_NULL;
        }
        else if(n == 0) {
            logMessage(ERROR, "client quit-%d:%s", errno, strerror(errno));
            close(pfds[pos].fd);
            pfds[pos].fd = FD_NULL;
        }
        // 3. 数据获取成功
        else {
            buf[n] = 0;
            logMessage(NORMAL, "client received: %s", buf);
        }
    }

    // debug fd show
    void show_fd_map() {
        logMessage(DEBUG, "current waiting fds: ");
        for(int i = 0; i < max_fds; ++i) {
            if(pfds[i].fd == FD_NULL) continue;
            std::cout << pfds[i].fd << " ";
        }
        std::cout << std::endl;
    }

private:
    int listen_sock;
    Sock m_sock;
    struct pollfd* pfds;        // poll结构体数组，个数由max_fds决定
    static const nfds_t max_fds = 1000;
    int m_timeout = 2000;
};

#endif