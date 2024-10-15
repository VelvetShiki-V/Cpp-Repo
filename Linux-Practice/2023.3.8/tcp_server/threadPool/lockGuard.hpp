#ifndef __LOCKGUARD_HPP
#define __LOCKGUARD_HPP
#pragma once
#include <iostream>
#include <pthread.h>

class Mutex{
public:
    Mutex(pthread_mutex_t* mtx)
    :m_mtx(mtx)
    {}
    void lock() {
        pthread_mutex_lock(m_mtx);
    }
    void unlock() {
        pthread_mutex_unlock(m_mtx);
    }
    ~Mutex(){}
private:
    pthread_mutex_t* m_mtx;
};

class lockGuard {
public:
    lockGuard(pthread_mutex_t* mtx)
    :lock_mtx(mtx)
    {
        lock_mtx.lock();
        logMessage(DEBUG, "线程已加锁");
    }
    ~lockGuard() {
        lock_mtx.unlock();
        logMessage(DEBUG, "线程已解锁");
    }
private:
    Mutex lock_mtx;
};

#endif