#include <iostream>
#include <pthread.h>
#include <string>

typedef void*(*func_t)(void*);      // 传入回调方法使线程执行相应功能

class ThreadData{       // 线程属性，需在构造初始化阶段将信息填充
public:
    std::string m_name;
    void* args;
};

class Thread{
public:
    // 1. 线程初始化，填充线程[编号，参数，回调方法]
    Thread(int num, void* args, func_t function)
    :callback(function)
    {
        td = new ThreadData();
        thread_name = "thread-" + std::to_string(num);
        td->m_name = thread_name;
        td->args = args;
    }

    // 2. 启动线程，执行指定任务
    void start() {
        pthread_create(&m_tid, nullptr, callback, (void*)td->args);
    }

    // 3. 回收线程
    void join() {
        pthread_join(m_tid, nullptr);
    }

    // 4. 将线程名暴露
    const std::string& name() {
        return thread_name;
    }
private:
    pthread_t m_tid;        // 属性字段封装
    std::string thread_name;
    func_t callback;
    ThreadData* td;
};