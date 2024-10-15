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
#include <sys/wait.h>
#include <unordered_map>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>     // 网络头文件4件套
#include "log.hpp"
#include "./threadPool/threadPool.hpp"
#include "./threadPool/task.hpp"
#define SIZE 1024

// 子进程给客户端主机提供数据通信IO服务
static void CEDict(int fd, const std::string& cli_ip, const uint16_t& cli_port, const std::string& name) {
    // logMessage(NORMAL, "pid:%d 为您服务", getpid());
    logMessage(NORMAL, "%s为您服务", name.c_str());
    static std::unordered_map<std::string, std::string> dict = {
        {"senate", "参议院"}
        ,{"ridiculous", "荒谬"}
        ,{"express", "快递"}
        ,{"enquiry", "询问"}
        ,{"instruct", "教导"}
        ,{"solidify","固化"}
        ,{"hello","金融"}
        ,{"commerce","金融"}
        ,{"你好","hi"}
        ,{"很好","nice"}
    };
    char buf[SIZE];
    ssize_t s = read(fd, buf, sizeof buf - 1);      // 将网络数据读取到本地缓冲区中，打印输出
    if(s > 0) {
        buf[s] = 0;
        std::string src = buf;
        std::cout << "#" << name.c_str() << " gets from[" << cli_ip << "-" << cli_port << "]: "<< buf << std::endl;
        // 英翻汉
        auto result = dict.find(src);
        if(result == dict.end()) {
            dict.insert({src, "等待更新中..."});
            src = "词库未收录，整不成";
            logMessage(ERROR, "%s", "没有对应源");
        }
        else {
            src = result->second;
            logMessage(NORMAL, "%s", "词源已获取，推送反馈并等待");
        }
        ssize_t t = write(fd, src.c_str(), src.size());     // echo service响应式服务器
        assert(t != -1);
        logMessage(NORMAL, "%s", "data turns back to client succ");
    }
    else if(s == 0) {        // 对端（写）关闭连接，此时读端也关闭
        logMessage(WARNING, "[%s-%d] quits, service shut down", cli_ip.c_str(), cli_port);
    }
    else {
        logMessage(ERROR, "service read error, %d:%s", errno, strerror(errno));
    }
    close(fd);
}

class ThreadData{
public:
    ThreadData(int sock, const std::string& ip, uint16_t port)
    :m_sock(sock)
    ,m_ip(ip)
    ,m_port(port)
    {}
    int m_sock;
    std::string m_ip;;
    uint16_t m_port;
};

class TcpServer{
public:
    TcpServer(uint16_t port, std::string ip = "", int sock = -1)
    :m_port(port)
    ,m_ip(ip)
    ,listen_sock(sock)
    ,tp_ptr(ThreadPool<Task>::getThreadPool())
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
        logMessage(NORMAL, "开始服务");
        tp_ptr->run();
        while(true) {
            // signal(SIGCHLD, SIG_IGN);       // 忽略子进程退出，子进程自动释放僵尸状态
            sockaddr_in fromClient;         // 建立通信服务套接字（自动填充通信主机IP和端口）
            socklen_t len = sizeof(fromClient);

            // accept用于使父进程获取一个新连接，并将该服务（套接字）转交于子进程手中
            int service_sock = accept(listen_sock, (sockaddr*)&fromClient, &len);
            if(service_sock < 0) {
                logMessage(ERROR, "accept fail, %d:%s", errno, strerror(errno));
                continue;
            }

            // 信息暂存，将用于任务队列回调函数中
            uint16_t cli_port = ntohs(fromClient.sin_port);
            std::string cli_ip = inet_ntoa(fromClient.sin_addr);
            logMessage(NORMAL, "server accepts user[%s-%d] successfully", cli_ip.c_str(), cli_port);  
            
            // // 多进程版本1：父进程继续为其他客户端提供服务，子进程阻塞式收发数据
            // pid_t id = fork();
            // assert(id != -1);
            // if(id == 0) {
            //     close(listen_sock);     // 实际给客户端提供服务的是子进程和包含其网络服务信息的service_sock套接字，listen仅用于监听
            //     service(service_sock, cli_ip, cli_port);
            //     exit(0);        // 服务完成，子进程退出（发送信号给父进程并忽略）
            // }
            // close(service_sock);        // 父进程不具体为客户端通信提供服务，所以需要将服务套接字关闭，防止可用套接字越来越少
        

            // 多进程版本2：孙子孤儿进程（子进程fork后立即退出，孙子进程被OS领养，不会阻塞父进程）
            // pid_t id = fork();
            // assert(id != -1);
            // if(id == 0) {
            //     close(listen_sock);     // 实际给客户端提供服务的是子进程和包含其网络服务信息的service_sock套接字，listen仅用于监听
            //     if(fork() > 0) {
            //         logMessage(WARNING, "pid:%d 将退出，孙子进程将继续提供服务", getpid());
            //         exit(3);        // 子进程退出
            //     }
            //     service(service_sock, cli_ip, cli_port);    // 孙子进程在提供服务，但由于其父进程已退出，所以被OS领养，在退出时也会将被OS回收
            //     exit(4);        // 孙子进程执行完毕自动退出，OS领养
            // }
            // waitpid(id, nullptr, 0);        // 父进程阻塞式回收（若子进程不退出，则阻塞式等待）
            // close(service_sock); 


            // 多线程版本3:
            // pthread_t tid;
            // ThreadData* td = new ThreadData(service_sock, cli_ip, cli_port);
            // pthread_create(&tid, nullptr, threadRoutine, (void*)td);
            // 多线程中不需要关闭父进程创建的文件描述符listen_sock，因为新线程与主线程共享


            // 线程池版本4:
            Task t(service_sock, cli_ip, cli_port, CEDict);        // service会任务执行的回调方法，为客户端提供服务
            tp_ptr->taskPush(t);        // 将制作好的任务推到任务队列中
            logMessage(NORMAL, "任务处理完成");
        }   // 因为子进程会继承父进程文件描述符表，且父进程修改时，子进程写时拷贝，不会互相影响
    }

    ~TcpServer() {
        if(listen_sock >= 0) {      // 析构时，如果监听套接字仍处于连接状态，关闭它
            close(listen_sock);
        }
    }

private:
    static void* threadRoutine(void* argss) {
        pthread_detach(pthread_self());
        logMessage(NORMAL, "tid:%d 将为您服务", pthread_self());
        ThreadData* td = static_cast<ThreadData*>(argss);
        CEDict(td->m_sock, td->m_ip, td->m_port, std::to_string(pthread_self()));
        return nullptr;
    }

private:
    uint16_t m_port;
    std::string m_ip;
    int listen_sock;
    std::unique_ptr<ThreadPool<Task>> tp_ptr;
};

#endif