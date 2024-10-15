#ifndef __SELECTSERVER_HPP
#define __SELECTSERVER_HPP
#include <iostream>
#include "sock.hpp"
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
using std::string;
#define FD_MAX (sizeof(fd_set) * 8)
#define FD_NULL -1
#define SIZE 1024

class selectServer{
public:
    selectServer(const uint16_t& port = 8080) {
        listen_sock = m_sock.socket_create();       // 连接三板斧
        m_sock.server_bind(listen_sock, "", port);
        m_sock.server_listen(listen_sock);
        for(int i = 0; i < FD_MAX; ++i) {
            fd_map[i] = FD_NULL;
        }
        fd_map[0] = listen_sock;        // 初始化时将listen_sock设置为第一个监视的套接字，整个进程运行期间需要不断通过该接口监管连接的请求接入
        logMessage(DEBUG, "server init done, listen_sock: %d, listening...", listen_sock);
    }
    ~selectServer() {
        if(listen_sock >= 0) close(listen_sock);
    }
    void run() {
        while(true) {
            // debug
            show_fd_map();
            // 1. 每次循环检测服务套接字，重置监视位图rfds
            fd_set rfds;
            FD_ZERO(&rfds);
            int nfds_max = listen_sock;
            // 2. 将监视中的套接字从用户态IO数组设置如位图中
            for(int i = 0; i < FD_MAX; ++i) {
                if(fd_map[i] == FD_NULL) continue;
                FD_SET(fd_map[i], &rfds);
                if(fd_map[i] > nfds_max) nfds_max = fd_map[i];      // 将最大值套接字更新
            }
            // 3. 进行select阻塞式监视等待+通知
            int fds = select(nfds_max + 1, &rfds, nullptr, nullptr, nullptr);    // 设为nullptr为阻塞等待，0非阻塞，timeval为定时等待    
            switch(fds) {
                case 0: {
                    logMessage(ERROR, "fds is unavailable");
                    break;
                }
                case -1: {
                    logMessage(ERROR, "select error-%d:%s", errno, strerror(errno));
                    break;
                }
                default: {
                    logMessage(DEBUG, "select success, count: %d fds are ready to handle", fds);
                    handler(rfds);      // 监视+等待检测成功，调用对应方法处理客户端IO连接接入
                    break;
                }
            }
        }
    }

    void handler(const fd_set& rfds) {
        // 1. 循环遍历用户态数组检测传入的输出型rfds中是否被检测为就绪套接字
        for(int i = 0; i < FD_MAX; ++i) {
            if(fd_map[i] == FD_NULL) continue;
            if(FD_ISSET(fd_map[i], &rfds)) {
                if(fd_map[i] == listen_sock) {
                    logMessage(DEBUG, "fd type: connection");
                    accepter();
                }
                else { 
                    logMessage(DEBUG, "fd type: data receive");
                    receiver(i);
                }
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
        // 2. 检测当前套接字是否有剩余监视位可插入
        int pos = 1;
        for(pos; pos < FD_MAX; ++pos) {     // 必须遍历，因为中间可能会存在可用套接字位置
            if(fd_map[pos] == FD_NULL) break;       // 当有空位则插入
        }
        if(pos == FD_MAX) {
            logMessage(ERROR, "serving socks are full, current sock is denied");
            close(service_sock);
        }
        // 3. 将服务套接字置入用户态IO数组中，用以后续侦测数据读取IO行为
        else {
            logMessage(DEBUG, "cur sock is accepted, sock: %d", service_sock);
            fd_map[service_sock] = service_sock;
        }
    }
    
    // 内核态检测IO行为是service_sock缓冲区资源就绪，准备recv拷贝数据
    void receiver(const int& pos) {
        // 1. 定义用户态缓冲区，接收缓冲区资源拷贝
        char buf[SIZE];
        ssize_t n = recv(fd_map[pos], buf, sizeof buf - 1, 0);
        // 2. 差错处理，读取失败或对端关闭，将套接字关闭并从用户态监视数组中去除
        if(n < 0) {
            logMessage(ERROR, "data receive fail-%d:%s", errno, strerror(errno));
            close(fd_map[pos]);
            fd_map[pos] = FD_NULL;
        }
        else if(n == 0) {
            logMessage(ERROR, "client quit-%d:%s", errno, strerror(errno));
            close(fd_map[pos]);
            fd_map[pos] = FD_NULL;
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
        for(int i = 0; i < FD_MAX; ++i) {
            if(fd_map[i] == FD_NULL) continue;
            std::cout << fd_map[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    int listen_sock;
    int fd_map[FD_MAX];     // 用户态IO数组--映射给内核态文件描述符位图用
    Sock m_sock;
};

#endif