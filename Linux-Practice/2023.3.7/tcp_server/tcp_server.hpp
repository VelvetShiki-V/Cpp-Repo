#ifndef __TCP_SERVER_HPP
#define __TCP_SERVER_HPP
#pragma once

#include <iostream>
#include <errno.h>
#include <cstring>
#include <signal.h>
#include <string>
#include <cassert>
#include <memory>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>
#include <arpa/inet.h>
#include "log.hpp"
#define SIZE 1024

// 子进程给客户端主机提供数据通信IO服务
static void service(int fd, const std::string& cli_ip, const uint16_t& cli_port) {
    while(true) {
        char buf[SIZE];
        ssize_t s = read(fd, buf, sizeof buf);      // 将网络数据读取到本地缓冲区中，打印输出
        if(read > 0) {
            buf[s] = 0;
            std::cout << cli_ip << "-" << cli_port << ": "<< buf << std::endl;
        }
        else if(read == 0) {        // 接收到数据为0，代表对端（写）关闭连接，此时读端也关闭
            logMessage(WARNING, "[%s-%d] quits, service shut down", cli_ip.c_str(), cli_port);
            break;
        }
        else {
            logMessage(ERROR, "service read error, %d:%s", errno, strerror(errno));
            break;
        }
        ssize_t t = write(fd, buf, strlen(buf));     // echo service响应式服务器
        assert(t != -1);
    }

}

class TcpServer{
public:
    TcpServer(uint16_t port, std::string ip = "", int sock = -1)
    :m_port(port)
    ,m_ip(ip)
    ,listen_sock(sock)
    {}

    void init() {       // 初始化三板斧：创建socket（tcp监听版），网络服务绑定bind，listen开始监听
        listen_sock = socket(AF_INET, SOCK_STREAM, 0);
        if(listen_sock < 0) {
            logMessage(FATAL, "listen fail, %d:%s", errno, strerror(errno));
            exit(1);
        }
        logMessage(NORMAL, "server socket create done");
        sockaddr_in server;
        bzero(&server, sizeof server);
        server.sin_addr.s_addr = m_ip.empty() ? INADDR_ANY : inet_addr(m_ip.c_str());
        server.sin_family = PF_INET;
        server.sin_port = htons(m_port);
        if(bind(listen_sock, (sockaddr*)&server, sizeof server) < 0) {
            logMessage(FATAL, "bind error, %d:%s", errno, strerror(errno));
            exit(2);
        } 
        logMessage(NORMAL, "server socket bind done");
        int backlog = 20;
        int l = listen(listen_sock, backlog);
        if(l < 0) {
            logMessage(FATAL, "listen fail, %d:%s", errno, strerror(errno));
            exit(3);
        }
        logMessage(NORMAL, "server socket listen done");
    }

    void start() {          // 开始服务（多进程版本——父进程监听待通信主机，子进程提供服务）
        while(true) {
            signal(SIGCHLD, SIG_IGN);       // 忽略子进程退出，子进程自动释放僵尸状态
            sockaddr_in fromClient;         // 建立通信服务套接字（自动填充通信主机IP和端口）
            uint16_t cli_port = ntohs(fromClient.sin_port);
            std::string cli_ip = inet_ntoa(fromClient.sin_addr);
            fromClient.sin_family = AF_INET;
            socklen_t len = sizeof(fromClient);

            // accept用于使父进程获取一个新连接，并将该服务（套接字）转交于子进程手中
            int service_sock = accept(listen_sock, (sockaddr*)&fromClient, &len);
            if(service_sock < 0) {
                logMessage(ERROR, "accept fail, %d:%s", errno, strerror(errno));
                continue;
            }
            logMessage(NORMAL, "server accepts user successfully");  
            // 父进程继续为其他客户端提供服务，子进程阻塞式收发数据
            pid_t id = fork();
            assert(id != -1);
            if(id == 0) {
                close(listen_sock);     // 实际给客户端提供服务的是子进程和包含其网络服务信息的service_sock套接字，listen仅用于监听
                service(service_sock, cli_ip, cli_port);
                exit(0);        // 服务完成，子进程退出（发送信号给父进程并忽略）
            }
            close(service_sock);        // 父进程不具体为客户端通信提供服务，所以需要将服务套接字关闭，防止可用套接字越来越少
        }               // 因为子进程会继承父进程文件描述符表，且父进程修改时，子进程写时拷贝，不会互相影响

    }

    ~TcpServer() {
        if(listen_sock >= 0) {      // 析构时，如果监听套接字仍处于连接状态，关闭它
            close(listen_sock);
        }
    }

private:
    uint16_t m_port;
    std::string m_ip;
    int listen_sock;
};

#endif