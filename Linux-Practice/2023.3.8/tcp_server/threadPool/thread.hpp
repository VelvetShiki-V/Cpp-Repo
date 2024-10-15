#ifndef __THREAD_HPP
#define __THREAD_HPP
#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include <functional>
#include <pthread.h>
#include "../log.hpp"

typedef void*(*func_)(void*);      // 回调函数类型

class ThreadDat{
public:
    std::string td_name;
    void* m_args;
};

class Thread{
public:
    Thread(int num, func_ func, void* arg)
    :callback(func)
    {
        std::string thread_name = "thread-" + std::to_string(num);
        m_td.m_args = arg;
        m_td.td_name = thread_name;
    }
    void start() {
        pthread_create(&tid, nullptr, callback, (void*)&m_td);
        logMessage(NORMAL, "%s create successfully", m_td.td_name.c_str());
    }
    void join() {
        pthread_join(tid, nullptr);
    }
    const std::string& getName() {
        return m_td.td_name;
    }
private:
    pthread_t tid;
    func_ callback;     // threadRoutine
    ThreadDat m_td;
};

#endif