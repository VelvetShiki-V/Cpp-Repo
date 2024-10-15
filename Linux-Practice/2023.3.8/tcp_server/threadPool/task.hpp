#ifndef __TASK_HPP
#define __TASK_HPP
#pragma once
#include <iostream>
#include <functional>
#include <string>

using func_t = std::function<void(int, std::string, uint16_t, std::string)>;
// 等价于：typedef void(*func_t)(int, int);
// 等价于：typedef std::function<void(int, int)> func_t;

class Task{
public:
    Task(){}
    Task(int sock, const std::string& ip, const uint16_t& port, func_t func)
    :service_sock(sock)
    ,cli_ip(ip)
    ,cli_port(port)
    ,service_task(func)
    {}
    void operator()(std::string name) {
        service_task(service_sock, cli_ip, cli_port, name);     // 执行tcp_server中的service方法
    }
private:
    int service_sock;
    std::string cli_ip;
    uint16_t cli_port;
    func_t service_task;
};

#endif