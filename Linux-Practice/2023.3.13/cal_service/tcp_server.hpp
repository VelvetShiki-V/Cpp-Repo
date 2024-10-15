#ifndef __TCP_SERVER
#define __TCP_SERVER
#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <cstring>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include "log.hpp"
#include "sock.hpp"
#include "protocol.hpp"

using func_t = std::function<void(int sock)>;

class TcpServer;
class ThreadData{
public:
    ThreadData(const int& sock, TcpServer* tp)
    :td_sock(sock)
    ,td_server(tp)
    {}
    int td_sock;
    TcpServer* td_server;
};

class TcpServer{
private:
    static void* threadRoutine(void* args) {
        pthread_detach(pthread_self());
        ThreadData* td = static_cast<ThreadData*>(args);
        td->td_server->execution(td->td_sock);
        close(td->td_sock);
        delete td;
        logMessage(NORMAL, "task finished, ready for the next...");
        return nullptr;
    }

public:
    TcpServer(const uint16_t& port, const std::string ip = "0.0.0.0")
    {
        m_socket = m_sock.sock_create();
        m_sock.sock_bind(ip, port, m_socket);
        m_sock.client_listen(m_socket);
        logMessage(NORMAL, "TcpServer initialization done");
    }

    void exe_registration(func_t func) {
        m_callbacks.push_back(func);
        logMessage(NORMAL, "task registration done");
    }

    void execution(int sock) {
        logMessage(DEBUG, "callback.size(): %d", m_callbacks.size());
        for(auto& it: m_callbacks) {
            it(sock);
        }
        logMessage(NORMAL, "task execution done");
    }

    void start() {
        while(true) {
            std::string ip;
            uint16_t port;
            int service_sock = m_sock.service_accept(m_socket, ip, port);
            if(service_sock < 0) continue;
            ThreadData* td = new ThreadData(service_sock, this);
            pthread_t tid;
            pthread_create(&tid, nullptr, threadRoutine, (void*)td);
        }
    }

    ~TcpServer() {
        if(m_socket > 0) {
            close(m_socket);
            logMessage(NORMAL, "sock已关闭");
        }
    }
private:
    int m_socket;
    Sock m_sock;
    std::vector<func_t> m_callbacks;
};

#endif