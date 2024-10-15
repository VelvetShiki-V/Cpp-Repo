#ifndef __SOCK_HPP
#define __SOCK_HPP
#pragma once
#include <iostream>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include "log.hpp"
#include <cerrno>
using std::string;

class Sock{
public:
    static int socket_create() {
        int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
        if(listen_sock < 0) {
            logMessage(FATAL, "socket create-%d:%s", errno, strerror(errno));
            exit(1);
        }
        // 服务器地址复用
        int opt = 1;
        setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof opt);
        return listen_sock;
    }

    static void socket_bind(const int& listen_sock, const uint16_t& port = 8080, const string& ip = "") {
        sockaddr_in local;
        bzero(&local, sizeof local);
        local.sin_addr.s_addr = ip.empty() ? INADDR_ANY : inet_addr(ip.c_str());
        local.sin_port = htons(port);
        local.sin_family = AF_INET;
        if(bind(listen_sock, (sockaddr*)&local, sizeof local) < 0) {
            logMessage(FATAL, "service sock bind-%d:%s", errno, strerror(errno));
        }
    }

    static void service_listen(const int& listen_sock) {
        if(listen(listen_sock, gbacklog) < 0) {
            logMessage(FATAL, "service listen-%d:%s", errno, strerror(errno));
        }
    }

    static int client_accept(const int& listen_sock, string* ip, uint16_t* port) {
        sockaddr_in fromClient;
        socklen_t len = sizeof fromClient;
        bzero(&fromClient, len);
        int service_sock = accept(listen_sock, (sockaddr*)&fromClient, &len);
        if(service_sock < 0) {
            logMessage(ERROR, "client accept fail-%d:%s", errno, strerror(errno));
            return -1;
        }
        if(ip) *ip = inet_ntoa(fromClient.sin_addr);
        if(port) *port = ntohs(fromClient.sin_port);
        return service_sock;
    }
private:
    static const int gbacklog = 10;
};

#endif