#ifndef __SOCK_HPP
#define __SOCK_HPP
#pragma once
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "log.hpp"
using std::string;

class Sock {
public:
    // 创建套接字
    static int socket_create() {
        int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
        if(listen_sock < 0) {
            logMessage(FATAL, "sock create failed-%d:%s", errno, strerror(errno));
            exit(1);
        }
        // 地址复用
        int opt = 1;
        setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof opt);
        return listen_sock;
    }
    // 服务器绑定listen_sock
    static void service_bind(const int& listen_sock, const uint16_t port = default_port, const string& ip = default_ip) {
        sockaddr_in local;
        bzero(&local, sizeof local);
        local.sin_addr.s_addr = ip.empty() ? INADDR_ANY : inet_addr(ip.c_str());
        local.sin_port = htons(port);
        local.sin_family = AF_INET;
        if(bind(listen_sock, (sockaddr*)&local, sizeof local) < 0) {
            logMessage(FATAL, "service bind sock failed-%d:%s", errno, strerror(errno));
            exit(2);
        }
    }
    // 客户端请求监听
    static void service_listen(const int& listen_sock) {
        if(listen(listen_sock, gbacklog) < 0) {
            logMessage(FATAL, "service listen failed-%d:%s", errno, strerror(errno));
            exit(3);
        }
    }
    // 服务器获取新的客户端连接
    static int client_accept(const int& listen_sock, string* client_ip, uint16_t* client_port, int* err) {
        sockaddr_in client;
        socklen_t len = sizeof client;
        bzero(&client, len);
        int service_sock = accept(listen_sock, (sockaddr*)&client, &len);
        if(service_sock < 0) {
            // logMessage(ERROR, "client accept failed-%d:%s", errno, strerror(errno));
            if(err) *err = errno;
            return -1;
        }
        if(client_ip) *client_ip = inet_ntoa(client.sin_addr);
        if(client_port) *client_port = ntohs(client.sin_port);
        if(err) *err = errno;
        return service_sock;
    }
    // 套接字非阻塞IO
    static bool sock_non_block(int& sock) {
        int fl = fcntl(sock, F_GETFL);          // 获取标记位
        if(fl < 0) {
            perror("fcntl:");
            return false;
        }
        fcntl(sock, F_SETFL, O_NONBLOCK);       // 对标记位设置非阻塞IO
        return true;
    }
    // 客户端ip port绑定套接字，与服务器建立连接
    static bool connect_to_server(const int& service_sock, const string& client_ip, const uint16_t& port) {
        sockaddr_in client;
        bzero(&client, sizeof client);
        client.sin_addr.s_addr = inet_addr(client_ip.c_str());
        client.sin_port = htons(port);
        client.sin_family = AF_INET;
        if(connect(service_sock, (sockaddr*)&client, sizeof client) == 0) return true;
        else return false;
    }
    // 客户端写入
    static void msg_send(const int& sock, const string& s) {
        ssize_t n = send(sock, s.c_str(), s.size(), 0);
    }
    // 客户端读取
    static string msg_get(const int& sock) {
        char output_buffer[1024];
        ssize_t n = recv(sock, output_buffer, sizeof output_buffer - 1, 0);
        output_buffer[n] = 0;
        return output_buffer;
    }
private:
    static const uint16_t default_port = 8080;
    static const int gbacklog = 10;
    static const string default_ip;
};
const string Sock::default_ip = "";

#endif