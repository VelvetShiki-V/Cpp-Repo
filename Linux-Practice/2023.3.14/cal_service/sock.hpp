#ifndef __SOCK_HPP
#define __SOCK_HPP
#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "log.hpp"

// 套接字通用类，提供给服务器和客户端通信使用，面向对象
class Sock{
public:
    Sock(){}
    ~Sock(){}
    // 1. 创建套接字
    int sock_create() {
        int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(listen_socket < 0) {
            logMessage(FATAL, "%d:%s", errno, strerror(errno));
            exit(1);
        }
        logMessage(NORMAL, "sock create done");
        return listen_socket;
    }

    // 2. 服务器监听客户端请求
    void client_listen(const int& socket) {
        if(listen(socket, backlog) < 0) {
            logMessage(FATAL, "%d:%s", errno, strerror(errno));
            exit(2);
        }
        logMessage(NORMAL, "server listening...");
    }

    // 3. 服务器ip端口与客户端绑定
    void sock_bind(const std::string& ip, const uint16_t& port, const int& socket) {
        sockaddr_in local_server;
        bzero(&local_server, sizeof local_server);
        local_server.sin_addr.s_addr = inet_addr(ip.c_str());
        local_server.sin_port = htons(port);
        local_server.sin_family = AF_INET;
        if(bind(socket, (sockaddr*)&local_server, sizeof local_server) < 0) {
            logMessage(FATAL, "%d:%s", errno, strerror(errno));
            exit(3);
        }
        logMessage(NORMAL, "server bind done");
    }

    // 4. 服务器接收客户端请求
    int service_accept(const int& socket, std::string& ip, uint16_t& port) {
        sockaddr_in fromClient;
        socklen_t len = sizeof fromClient;
        int service_sock = accept(socket, (sockaddr*)&fromClient, &len);        // 服务套接字，与客户端进行数据传输的具体的IO接口
        if(service_sock < 0) {
            logMessage(ERROR, "%d:%s", errno, strerror(errno));
        }
        if(ip.c_str()) ip = inet_ntoa(fromClient.sin_addr);
        if(port) port = ntohs(fromClient.sin_port);
        logMessage(NORMAL, "client quest accept done");
        return service_sock;
    }

    // 5. 客户端与服务器进行TCP连接使用的连接接口
    void CSconnet(const int& sockfd, const std::string& ip, const std::string& port) {
        sockaddr_in toServer;
        bzero(&toServer, sizeof toServer);
        toServer.sin_addr.s_addr = inet_addr(ip.c_str());
        toServer.sin_port = htons(atoi(port.c_str()));
        toServer.sin_family = AF_INET;
        int flag = connect(sockfd, (sockaddr*)&toServer, sizeof toServer);
        if(flag < 0) {
            std::cout << "connect error" << std::endl;
            exit(2);
        }
    }

private:
    const static int backlog = 20;
};

#endif