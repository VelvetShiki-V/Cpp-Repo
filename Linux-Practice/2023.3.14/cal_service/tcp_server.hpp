#ifndef __TCP_SERVER
#define __TCP_SERVER
#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <cstring>
#include "signal.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include "log.hpp"
#include "sock.hpp"
#include "protocol.hpp"
#include "daemon.hpp"

using func_t = std::function<void(int sock)>;

// 线程数据类，包含网络套接字和server类（方便线程访问成员方法和属性）
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

// tcp服务器类
class TcpServer{
private:
    // 线程回调函数，线程需执行此方法以调用客户所需对应服务
    static void* threadRoutine(void* args) {
        pthread_detach(pthread_self());             // 线程分离，线程关闭不影响主线程运行
        ThreadData* td = static_cast<ThreadData*>(args);
        td->td_server->execution(td->td_sock);      // 调用注册过的服务器方法
        close(td->td_sock);
        delete td;
        logMessage(NORMAL, "task finished, ready for the next...");
        return nullptr;
    }

public:
    // 1. 服务器初始化将自动完成：进程守护（后台服务），套接字创建，客户端绑定，请求监听
    TcpServer(const uint16_t& port, const std::string ip = "0.0.0.0")
    {
        ProcGuard::Daemon();
        m_socket = m_sock.sock_create();
        m_sock.sock_bind(ip, port, m_socket);
        m_sock.client_listen(m_socket);
        logMessage(NORMAL, "TcpServer initialization done");
    }

    // 2. 服务器启动
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

    // 3. 服务方法注册
    void exe_registration(func_t func) {
        m_callbacks.push_back(func);
        logMessage(NORMAL, "task registration done");
    }

    // 4. 服务执行
    void execution(int sock) {
        logMessage(DEBUG, "callback.size(): %d", m_callbacks.size());
        for(auto& it: m_callbacks) {
            it(sock);       // 传入sock以使线程可通过套接字获取recv到客户端信息，并通过send予以反馈
        }
        logMessage(NORMAL, "task execution done");
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