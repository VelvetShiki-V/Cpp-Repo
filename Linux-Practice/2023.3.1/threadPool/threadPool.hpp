#pragma once
#include "thread.hpp"
#include "lockGuard.hpp"
using namespace std;

int default_thread_num = 3;

template<class T>
class ThreadPool{       // 线程池本质也是一个生产消费模型
public:
    ThreadPool(int num = default_thread_num)        // 默认构造参数为线程池的线程个数
    :m_num(num)
    {
        pthread_mutex_init(&m_mtx, nullptr);        // 同时将互斥锁和条件变量初始化，并将线程推入线程池中
        pthread_cond_init(&m_cond, nullptr);
        for(int i = 1; i <= num; ++i) {
            threads.push_back(new Thread(i, routine, this));       // 每个线程
        }
    }
    ~ThreadPool(){      // 线程池析构将锁与变量释放，以及释放线程池中的每个线程
        for(auto& iter: threads) {
            delete iter;
        }
        pthread_mutex_destroy(&m_mtx);
        pthread_cond_destroy(&m_cond);
    }

    // 提供给消费者线程的回调函数使用，因为是静态函数无this指针，必须将私有属性通过接口提供
    pthread_mutex_t* getMutex() {
        return &m_mtx;
    }

    // 若任务队列为空，消费者无法从队列中获取任务，必须挂起等待唤醒
    void waitCond() {
        pthread_cond_wait(&m_cond, &m_mtx);
    }

    // 消费者线程从任务队列获取任务
    T getTask() {
        T t = task_queue.front();
        task_queue.pop();
        return t;
    }

    bool isEmpty() {
        return task_queue.empty();
    }
    
    void run(){         // 启动线程池中的每个线程
        for(auto& iter: threads) {
            iter->start();
            logMessage(NORMAL, "%s %s\n", iter->name().c_str(), "启动成功");
        }
    }
    void end() {       // 释放线程池的每个线程
        for(auto& iter: threads) {
            iter->join();
            logMessage(WARNING, "%s %s\n", iter->name().c_str(), "已释放");
        }
    }
    void taskPush(const T& task){           // 生产者将任务推送至任务队列，唤醒消费者线程消费任务
        lockGuard lock(&m_mtx);
        task_queue.push(task);
        pthread_cond_signal(&m_cond);
    }
    static void* routine(void* args) {      // 回调方法必须为静态，否则存在this指针隐含在参数列表中
        ThreadData* td = (ThreadData*)args;
        ThreadPool<T>* tp = (ThreadPool<T>*)td->m_args;
        while(true) {
            T task;         // 消费者定义任务对象后，加锁进入任务队列的临界资源区，获取任务并执行任务
            {
                lockGuard lock(tp->getMutex());
                while(tp->isEmpty()) {tp->waitCond();}
                task = tp->getTask();
            }
            task(td->m_name);
        }
    }
private:
    vector<Thread*> threads;        // 线程池存储每个线程的地址
    queue<T> task_queue;            // 任务队列
    int m_num;                      // 一共有多少个线程
    pthread_mutex_t m_mtx;          // 互斥锁和条件变量对象
    pthread_cond_t m_cond;
};