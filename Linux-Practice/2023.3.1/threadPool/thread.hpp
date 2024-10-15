#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include <stdarg.h>
#include <cstdlib>
#include <functional>
#include <unistd.h>
#include <pthread.h>
#include "task.hpp"
#include "log.hpp"
using namespace std;

typedef void*(*func_t)(void*);      // 回调函数指针

class ThreadData{                   // 每个线程的参数信息
public:
    void* m_args;       // 线程属性和名称
    string m_name;
};

// 单个线程类
class Thread{
public:
    Thread(int num, func_t callback, void* args)
    :m_func(callback)
    {
        m_td.m_name = "thread-";
        m_td.m_name += to_string(num);
        m_td.m_args = args;
    }
    void start() {      // 创建并启动一个线程
        pthread_create(&tid, nullptr, m_func, (void*)&m_td);
    }
    void join() {       // 释放一个线程
        pthread_join(tid, nullptr);
    }
    string& name() {       // 暴露每个线程名字
        return m_td.m_name;
    }
private:
    pthread_t tid;          // 线程对象
    ThreadData m_td;
    func_t m_func;
};