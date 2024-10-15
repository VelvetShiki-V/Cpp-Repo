#ifndef __SOCK_HPP
#define __SOCK_HPP
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/fcntl.h>
#include "log.hpp"
using std::string;

class Sock{
public:
    Sock() {}
    ~Sock(){}
    // 1. 创建套接字
    int socket_create() {
        int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
        if(listen_sock < 0) {
            logMessage(FATAL, "socket create-%d:%s", errno, strerror(errno));
            exit(0);
        }
        // 服务器地址复用
        int opt = 1;
        setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
        return listen_sock;
    }

    // 2. 服务器与进程强关联
    void server_bind(const int& listen_sock, const string& ip = "", const uint16_t& port = 8080) {
        sockaddr_in local;
        bzero(&local, sizeof local);
        local.sin_addr.s_addr = ip.empty() ? INADDR_ANY : inet_addr(ip.c_str());
        // inet_pton(AF_INET, ip.c_str(), &local.sin_addr);
        local.sin_port = htons(port);
        local.sin_family = AF_INET;
        socklen_t local_len = sizeof local;
        if(bind(listen_sock, (sockaddr*)&local, local_len) < 0) {
            logMessage(FATAL, "bind-%d:%s", errno, strerror(errno));
            exit(2);
        }
    }

    // 3. 服务器监听
    void server_listen(const int& listen_sock) {
        if(listen(listen_sock, backlog) < 0) {
            logMessage(FATAL, "socket listen-%d:%s", errno, strerror(errno));
            exit(1);
        }
    }

    // 4. 获取已建立好的连接
    int client_accept(const int& listen_sock, string* ip, uint16_t* port) {
        sockaddr_in fromClient;             // ip port为输出型参数
        socklen_t len = sizeof fromClient;
        bzero(&fromClient, len);
        int service_sock = 0;
        if((service_sock = accept(listen_sock, (sockaddr*)&fromClient, &len)) < 0) {
            logMessage(ERROR, "accept-%d:%s", errno, strerror(errno));
            return -1;
        }
        if(ip) *ip = inet_ntoa(fromClient.sin_addr);        // 4字节ip转点分十进制字符串ip
        if(port) *port = ntohs(fromClient.sin_port);
        return service_sock;
    }

    
    // 客户端与服务器建立连接
    bool server_connect(const int& listen_sock, const string& ip, const uint16_t& port) {
        sockaddr_in addr;               // ip port为输入型参数，为客户端ip和port
        bzero(&addr, sizeof addr);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(port);
        addr.sin_family = AF_INET;
        socklen_t addr_len = sizeof addr;
        if(connect(listen_sock, (sockaddr*)&addr, addr_len) < 0) {
            // 客户端与服务器连接失败
            return false;
        }
        return true;
    }

private:
    int backlog = 10;
};
#endif