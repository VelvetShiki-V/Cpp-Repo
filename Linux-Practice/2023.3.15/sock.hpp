#ifndef __SOCK_HPP
#define __SOCK_HPP
#include <iostream>
#include <sys/types.h>
#include <cerrno>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "log.hpp"
#define SSIZE 10240

class Socket {
public:
    int socket_create() {
        int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(listen_socket < 0) {
            logMessage(FATAL, "socket create: %d:%s", errno, strerror(errno));
            exit(1);
        }
        logMessage(NORMAL, "socket create success, sock: %d", listen_socket);
        return listen_socket;
    }

    void socket_bind(const int& listen_sock, const uint16_t& server_port, const std::string& server_ip = "0.0.0.0") {
        sockaddr_in server_local;
        bzero(&server_local, sizeof server_local);
        server_local.sin_addr.s_addr = inet_addr(server_ip.c_str());
        server_local.sin_port = htons(server_port);
        server_local.sin_family = AF_INET;
        if(bind(listen_sock, (sockaddr*)&server_local, sizeof server_local) < 0) {
            logMessage(FATAL, "bind error: %d:%s", errno, strerror(errno));
            exit(2);
        }
        logMessage(NORMAL, "server local bind success");
    }

    void socket_listen(const int& listen_sock) {
        if(listen(listen_sock, backlog) < 0) {
            logMessage(FATAL, "client listen: %d:%s", errno, strerror(errno));
            exit(3);
        }
        logMessage(NORMAL, "server listening...");
    }

    int socket_accept(const int& listen_sock, std::string& cli_ip , uint16_t& cli_port) {
        sockaddr_in fromClient;
        socklen_t len = sizeof fromClient;
        int service_sock = accept(listen_sock, (sockaddr*)&fromClient, &len);
        if(service_sock < 0) {
            logMessage(ERROR, "client accept fail, %d:%s", errno, strerror(errno));
        }
        cli_ip = inet_ntoa(fromClient.sin_addr);
        cli_port = ntohs(fromClient.sin_port);
        logMessage(NORMAL, "client: ip[%s] port[%d] accept success", cli_ip.c_str(), cli_port);
        return service_sock;
    }

private:
    int backlog = 20;
};

std::string Recv(int service_sock) {
    char recbuf[SSIZE];
    ssize_t s = recv(service_sock, recbuf, sizeof recbuf, 0);
    if(s < 0) {
        logMessage(FATAL, "data obtained failed, %d:%s", errno, strerror(errno));
        exit(1);
    }
    else if(s == 0) {
        logMessage(ERROR, "对端关闭");
    }
    else {
        recbuf[s] = 0;
        logMessage(DEBUG, "接收到了数据:\n%s", recbuf);
        return recbuf;
    }
}

void Send(int service_sock, std::string str) {
    ssize_t s = send(service_sock, str.c_str(), str.size(), 0);
    if(s < 0) {
        logMessage(FATAL, "data sent fail, %d:%s", errno, strerror(errno));
        exit(2);
    }
    logMessage(NORMAL, "data sent success, str: %s", str.c_str());
}

#endif