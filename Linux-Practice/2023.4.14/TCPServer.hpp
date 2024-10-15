#ifndef __TCPSERVER_HPP
#define __TCPSERVER_HPP
#pragma once
#include <iostream>
#include <unordered_map>
#include <functional>
#include <cassert>
#include "sock.hpp"
#include "epoll.hpp"
#include "log.hpp"
#include "protocol.hpp"
#define IN_SIZE 1024

namespace reactor {
    class TCPServer;
    class SockBlock;
    using std::string;
    using func_t = std::function<void(reactor::SockBlock*)>;
    using task_t = std::function<void(string& s, reactor::SockBlock*)>;
    class SockBlock {
    public:
        SockBlock(const int& sock = -1): sockfd(sock)
        {
            in_buffer.resize(0);
            out_buffer.resize(0);
        }
        void set_callback(func_t read, func_t write, func_t except) {
            read_cb = read;
            write_cb = write;
            except_cb = except;
        }
    public:
        // 包含套接字，3个回调方法，2个缓冲区，1个回值指针
        int sockfd = -1;
        func_t read_cb;
        func_t write_cb;
        func_t except_cb;
        string in_buffer;
        string out_buffer;  
        TCPServer* _psvr;       // 回值指针可以让业务层指回服务器使epoll开启对该sock的读写监视权限
    };

    class TCPServer {
    public:
        TCPServer(const uint16_t port = default_port)
        :_port(port)
        ,_max_reps(default_reps_nums)
        {
            // 1. 服务器初始化
            _listen_sock = Sock::socket_create();
            Sock::service_bind(_listen_sock);
            Sock::service_listen(_listen_sock);
            // 2. epoll多路转接对象初始化
            _epoll.ep_create();
            // 3. listen_sock登记初始化(回调方法绑定类内成员函数)
            sock_registry(_listen_sock, std::bind(&TCPServer::acceptor, this, std::placeholders::_1), nullptr, nullptr);
            // 4. 构建一个获取就绪fd和事件的reps
            _reps = new epoll_event[_max_reps];
            logMessage(NORMAL, "server init done, listen_sock: %d, epoll_sock: %d", _listen_sock, _epoll.get_epfd());
        }
        ~TCPServer() {
            if(_listen_sock >= 0) close(_listen_sock);
            if(_reps) delete[] _reps;
        }

        // sock登记注册（创建block，插入epoll，添加映射）
        void sock_registry(int& sockfd, func_t read_handler, func_t write_handler, func_t except_handler) {
            // 1. 将当前sock设置为非阻塞（ET模式）
            if(!Sock::sock_non_block(sockfd)) assert(errno == 0);
            // 2. 将sock构建block并设置回调方法
            SockBlock* sb = new SockBlock(sockfd);
            sb->_psvr = this;
            sb->set_callback(read_handler, write_handler, except_handler);
            // 3. 将sock添加到epoll底层红黑树监视起来，默认打开只读监视
            if(!_epoll.epoll_add(sockfd)) assert(errno == 0);
            // 4. 添加sock和block*映射
            _sock_map[sockfd] = sb;
            logMessage(DEBUG, "sock: %d registration done", sockfd);
        }

        // server开始服务
        void dispatcher(task_t task) {
            _task = task;       // 业务方法初始化
            while(true) {
                act_each_loop();
            }
        }

        // server每次循环执行的任务
        void act_each_loop() {
            // wait得到需要处理的已就绪的fd个数
            int ready_nums = _epoll.ep_wait(_reps, _max_reps);
            for(int i = 0; i < ready_nums; ++i) {
                int sock = _reps->data.fd;
                uint32_t revent = _reps->events;
                if(revent & EPOLLIN) {
                    // sock只读IO事件就绪，该sock和对应只读方法必须存在于映射关系中
                    if(sock_existed(sock) && _sock_map[sock]->read_cb != nullptr) {
                        _sock_map[sock]->read_cb(_sock_map[sock]);      // 执行sock对应只读回调方法（bind方法手动传参在此）
                    }
                }
                else if(_reps[i].events & EPOLLOUT) {
                    // sock写IO事件就绪
                    if(sock_existed(sock) && _sock_map[sock]->write_cb != nullptr) {
                        _sock_map[sock]->write_cb(_sock_map[sock]);      // 执行sock对应只读回调方法（bind方法手动传参在此）
                    }
                }
                else if (_reps[i].events & EPOLLERR || _reps[i].events & EPOLLHUP) {
                    // sock异常IO事件就绪(HUP对端关闭，ERR监视错误)
                    if(sock_existed(sock) && _sock_map[sock]->except_cb != nullptr) {
                        _sock_map[sock]->except_cb(_sock_map[sock]);      // 执行sock对应只读回调方法（bind方法手动传参在此）
                    }
                }
            }
        }

        // 判断sock是否在哈希映射中
        bool sock_existed(const int& sock) {
            if(_sock_map.find(sock) != _sock_map.end()) return true;
            return false;
        }

        // sock监听新连接的读取IO事件
        void acceptor(SockBlock* sb){
            logMessage(NORMAL, "get a client");
            while(true) {
                string client_ip;
                uint16_t client_port;
                int err;
                int service_sock = Sock::client_accept(sb->sockfd, &client_ip, &client_port, &err);
                if(service_sock >= 0){
                    // 读取成功
                    // 注册sock(构建block，设置属性和回调方法，添加映射)
                    sock_registry(service_sock, std::bind(&TCPServer::receiver, this, std::placeholders::_1),
                                                std::bind(&TCPServer::writer, this, std::placeholders::_1),
                                                std::bind(&TCPServer::excepter, this, std::placeholders::_1));
                    logMessage(DEBUG, "client ip:[%s] port[%d], service_sock: %d accepted succ", client_ip.c_str(), client_port, service_sock);
                }
                else {
                    // 错误码被设置
                    if(err == EWOULDBLOCK || err == EAGAIN) {
                        // 资源未就绪
                        logMessage(ERROR, "no connection ready-%d:%s", errno, strerror(errno));
                    }
                    else if(err == EINTR) {
                        // 读取被信号中断
                        logMessage(ERROR, "client reception blocked by signal-%d:%s", errno, strerror(errno));
                        continue;
                    }
                    else {
                        // 读取错误
                        logMessage(ERROR, "client reception failed-%d:%s", errno, strerror(errno));
                    }
                    break;
                }
            }
        }

        // service sock数据流入只读IO事件
        void receiver(SockBlock* sb){
            bool err = false;
            while(true) {
                char in_buf[IN_SIZE];
                ssize_t n = recv(sb->sockfd, in_buf, sizeof(in_buf) - 1, 0);
                if(n > 0) {
                    // 1. 读取成功，数据流入用户层接收缓冲区，循环读取直至读取失败
                    in_buf[n] = 0;
                    sb->in_buffer += in_buf;
                }
                else if(n == 0) {
                    // 对端关闭
                    logMessage(ERROR, "client reading quit-%d:%s", errno, strerror(errno));
                    sb->except_cb(sb);
                    break;
                }
                else {
                    // 读取失败，三种情况
                    if(errno == EWOULDBLOCK) {
                        // 1. 资源未就绪
                        err = true;
                        // logMessage(ERROR, "inbuffer of fd read failed-%d:%s", errno, strerror(errno));
                    }
                    else if(errno == EINTR) {
                        // 2. 信号中断读取
                        logMessage(ERROR, "reading blocked by signal-%d:%s", errno, strerror(errno));
                        continue;
                    }
                    else {
                        // 3. 读取失败
                        logMessage(ERROR, "reading failed-%d:%s", errno, strerror(errno));
                        sb->except_cb(sb);
                    }
                    break;
                }
            }
            // 若到达此处，要么数据读取完整，要么读取失败
            if(err) {
                // 若接收缓冲区不为空，进行数据解析；若数据为空，说明只读数据的接收缓冲区未就绪，不做处理
                if(!sb->in_buffer.empty()) {
                    vector<string> msg;
                    decode(sb->in_buffer, msg);
                    // 交给业务逻辑处理数据
                    for(auto& it: msg) {
                        // logMessage(DEBUG, "开始对报文内容: %s进行处理", it.c_str());
                        task_handler(it, sb);
                    }
                }
            }
        }

        // sock写IO事件
        void writer(SockBlock* sb){
            // 1. epoll中打开对sock的读写监听
            if(!_epoll.ep_ctl(sb->sockfd, true, true)) {
                logMessage(ERROR, "writer failed-%d:%s", errno, strerror(errno));
                sb->except_cb(sb);
            }
            else {
                while(true) {
                    // 循环发送输出缓冲区中的已序列化且加密响应报文数据
                    ssize_t n = send(sb->sockfd, sb->out_buffer.c_str(), sb->out_buffer.size(), 0);
                    if(n > 0) {
                        // 发送成功，循环清除发送缓冲区内容，直至数据发送失败
                        sb->out_buffer.erase(0, n);
                        if(sb->out_buffer.empty()) {
                            logMessage(DEBUG, "sock: %d 数据发送完成，发送缓冲区已空", sb->sockfd);
                            break;
                        }
                    }
                    else if(n == 0) {
                        // 对端关闭，异常回调方法执行
                        logMessage(ERROR, "client quit");
                        sb->except_cb(sb);
                        break;
                    }
                    else {
                        // 发送失败，3种情况
                        // 资源未就绪/写入被信号中断/写入失败
                        if(errno == EWOULDBLOCK || errno == EAGAIN) break;
                        else if(errno == EINTR) continue;
                        else {
                            logMessage(ERROR, "sock: %d sending failed-%d:%s", errno, strerror(errno));
                            sb->except_cb(sb);      // 只有写入失败回调异常方法
                        }
                        break;
                    }
                }
                // 若数据发送完毕，将该sock的写权限暂时关闭，读权限依旧在epoll监视中
                if(sb->out_buffer.empty()) _epoll.ep_ctl(sb->sockfd, true, false);
                else _epoll.ep_ctl(sb->sockfd, true, true);
            }
        }

        // sock异常处理:
        void excepter(SockBlock* sb){
            // 先检查异常的sock是否存在
            assert(sb);
            if(!sock_existed(sb->sockfd)) return;
            // logMessage(ERROR, "sock handler conducting failed-%d:%s", errno, strerror(errno));
            // 将套接字去epoll, 去映射, close并释放block
            logMessage(DEBUG, "sock: %d throw exception, has been closed", sb->sockfd);
            _epoll.epoll_rmv(sb->sockfd);
            _sock_map.erase(sb->sockfd);
            close(sb->sockfd);
            free(sb);
        }

        // 服务器业务方法调用
        void task_handler(string& s, reactor::SockBlock* sb) {
            _task(s, sb);
        }

    private:
        int _listen_sock; 
        uint16_t _port;
        int _max_reps;      // 控制epoll一次可以获取的最大就绪fd个数
        task_t _task;       // 业务类方法注册
        Epoll _epoll;       // 底层epoll模型
        epoll_event* _reps; // 就绪结点结构体数组
        std::unordered_map<int, SockBlock*> _sock_map;      // fd与SockBlock映射
    private:
        static const uint16_t default_port = 8080;
        static const int default_reps_nums = 100;
    };
};


#endif