#pragma once
#include "thread.hpp"

// 互斥锁，封装加锁和解锁
class Mutex{
public:
    Mutex(pthread_mutex_t* mtx)
    :m_mtx(mtx)
    {
    }
    void lock() {
        pthread_mutex_lock(m_mtx);
        logMessage(DEBUG, "%s\n", "线程已加锁");
    }
    void unlock() {
        pthread_mutex_unlock(m_mtx);
        logMessage(DEBUG, "%s\n", "线程已解锁");
    }
private:
    pthread_mutex_t* m_mtx;
};

// RAII对象锁保护，对象创建即加锁，代码块结束对象释放即解锁
class lockGuard{
public:
    lockGuard(pthread_mutex_t* mtx)
    :m_mtx(mtx)
    {
        m_mtx.lock();
    }
    ~lockGuard() {
        m_mtx.unlock();
    }
private:
    Mutex m_mtx;
};