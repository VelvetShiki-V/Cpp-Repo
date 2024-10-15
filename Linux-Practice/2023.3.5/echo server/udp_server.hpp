#ifndef __UDP_SERVER_HPP
#define __UDP_SERVER_HPP
#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <memory>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "log.hpp"
#define SIZE 1024

// UDP服务器端类封装
class UdpServer{
public:
    // 服务器初始化有两步：IP和端口号填充，创建socket套接字并与进程绑定
    UdpServer(uint16_t port, std::string ip = "0.0.0.0", int in = -1)
    :m_port(port)       // ip和端口号为手动传入模式，仅能与特定主机的特定进程进行通信（局限）
    ,m_ip(ip)
    ,fd(in)             // 创建网络socket的文件描述符返回值，即与网络主机进行数据IO
    {}

    bool init() {
        // 1. 创建socket套接字（重要）
        fd = socket(AF_INET, SOCK_DGRAM, 0);        // 与网络主机进行IO通信，读取到服务器进程文件描述符中存储
        if(fd < 0) {
            logMessage(FATAL, "%d:%s", errno, strerror(errno));
            exit(1);
        }

        // 2. 将socket套接字（IP和端口号）与sockaddr（IP端口号字段），网络中该主机的该进程绑定起来
        sockaddr_in server;         // 将定义好的套接字进行属性填充，把需要与服务器通信的客户端IP和端口号填入，并准备发送和接收数据
        bzero(&server, sizeof server);
        server.sin_port = htons(m_port);        // 本地到网络，准备完成数据发送功能
        server.sin_addr.s_addr = inet_addr(m_ip.c_str());
        server.sin_family = AF_INET;
        if(bind(fd, (sockaddr*)&server, sizeof server) < 0) {       // 把socket套接字与属性绑定
            logMessage(FATAL, "%d: %s", errno, strerror(errno));
            exit(1);
        }
        logMessage(NORMAL, "server init complete... %s", strerror(errno));
        return true;
    }
    bool start() {
        logMessage(NORMAL, "server starts to listen...");
        char buf[SIZE];
        while(true) {       // 服务器进程永不退出
            sockaddr_in server;     // 从网络通信接收到的客户端发给服务器主机进程的套接字（地址类型+地址数据）
            socklen_t len = sizeof server;      // 输入输出型参数server即可以接收来自客户端的数据，也可以作为输出给客户端的套接字使用
            ssize_t t = recvfrom(fd, buf, sizeof buf, 0, (sockaddr*)&server, &len);      // 将读取到的文件写入buffer中
            if(t > 0) {
                logMessage(NORMAL, "server received data from client, processing...");
                // 辨明客户端身份
                uint16_t cli_port = ntohs(server.sin_port);
                // std::string ip = std::to_string(ntohs(server.sin_addr.s_addr)); 等价于下面接口inet_ntoa
                std::string cli_ip = inet_ntoa(server.sin_addr);
                // 打印接收到的内容
                buf[t] = 0;
                printf("#server receives from [%s] [%d]: %s\n", cli_ip.c_str(), cli_port, buf);
            }
            // 响应式服务器echo server，将数据原封不动返回给客户端
            sendto(fd, buf, sizeof buf, 0, (sockaddr*)&server, len);     // test
            // sendto(fd, buf, strlen(buf), 0, (sockaddr*)&server, len);
        }
        return true;
    }
    ~UdpServer() {
        if(fd >= 0) {
            close(fd);
        }
    }
private:
    uint16_t m_port;
    std::string m_ip;
    int fd;
};

#endif