#ifndef __THREADPOOL_HPP
#define __THREADPOOL_HPP
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cstdlib>
#include "lockGuard.hpp"
#include "../log.hpp"
#include "thread.hpp"
#include "task.hpp"

int default_thread_num = 5;

template<class T>
class ThreadPool{
public:
    void run() {
        for(auto& it: m_threads) {
            it->start();
            logMessage(NORMAL, "%s已启动", it->getName().c_str());
        }
    }

    ~ThreadPool() {
        for(auto& it: m_threads) {
            it->join();
            logMessage(NORMAL, "%s已回收", it->getName().c_str());
        }
        pthread_mutex_destroy(&m_mtx);
        pthread_cond_destroy(&m_cond);
    }

    void taskPush(const T& task) {
        lockGuard lock(&m_mtx);
        task_queue.push(task);
        pthread_cond_signal(&m_cond);
        logMessage(NORMAL, "任务已推送，唤醒消费线程");
    }

    void taskClaim(T* task) {
        *task = task_queue.front();
        task_queue.pop();
        logMessage(NORMAL, "线程任务已获取");
    }

    pthread_mutex_t* getMutex() {
        return &m_mtx;
    }

    void waitCond() {
        pthread_cond_wait(&m_cond, &m_mtx);
        logMessage(WARNING, "任务队列空，线程已挂起");
    }

    bool isEmpty() {
        return task_queue.empty();
    }

    static void* threadRoutine(void* args) {
        ThreadDat* td = (ThreadDat*)args;
        ThreadPool* tp = (ThreadPool*)td->m_args;
        while(true) {
            Task t;
            {
                lockGuard lock(tp->getMutex());
                while(tp->isEmpty()) tp->waitCond();
                tp->taskClaim(&t);      // 线程池中的消费者线程竞争从临界区任务队列获取任务，并执行
            }
            t(td->td_name);     // 将执行任务的线程名传入回调函数service中，表明执行的线程名信息
        }
        return nullptr;
    }

    static ThreadPool<T>* getThreadPool(int num = default_thread_num) {
        if(tp_ptr == nullptr) {
            logMessage(NORMAL, "线程池单例未获取, ready to get singletom");
            lockGuard lock(&mtx);
            if(tp_ptr == nullptr) {
                tp_ptr = new ThreadPool<T>(num);
                logMessage(NORMAL, "线程池已创建");
            }
        }
        return tp_ptr;
    }

private:
    ThreadPool(int num = default_thread_num)
    :thread_nums(num)
    {
        for(int i = 1; i <= thread_nums; ++i) {
            m_threads.push_back(new Thread(i, threadRoutine, this));
            logMessage(NORMAL, "%s已创建", m_threads[i - 1]->getName().c_str());
        }
        // logMessage(DEBUG, "%d", m_threads.size());
        // for(auto& it: m_threads) {
        //     logMessage(DEBUG, "%s", it->getName().c_str());
        // }
        pthread_mutex_init(&m_mtx, nullptr);
        pthread_cond_init(&m_cond, nullptr);
    }

    ThreadPool(const ThreadPool<T>& tp) = delete;
    const ThreadPool<Task>& operator=(const ThreadPool<Task>& tp) = delete;

private:
    int thread_nums;
    std::queue<T> task_queue;
    std::vector<Thread*> m_threads;
    pthread_mutex_t m_mtx;
    pthread_cond_t m_cond;

    static ThreadPool<T>* tp_ptr;
    static pthread_mutex_t mtx;
};

template<typename T>
ThreadPool<T>* ThreadPool<T>::tp_ptr = nullptr;
template<typename T>
pthread_mutex_t ThreadPool<T>::mtx = PTHREAD_MUTEX_INITIALIZER;

#endif