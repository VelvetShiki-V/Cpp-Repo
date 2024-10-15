#pragma once
#include <iostream>
#include <pthread.h>
using namespace std;

class Mutex{
public:
    Mutex(pthread_mutex_t* mtx)
        :m_mtx(mtx)
        {}
    void Lock() {
        pthread_mutex_lock(m_mtx);
    }
    void unlock() {
        pthread_mutex_unlock(m_mtx);
    }
private:
    pthread_mutex_t* m_mtx;
};

class lockGuard{
public:
    lockGuard(pthread_mutex_t* mtx)
        :mm_mtx(mtx) 
        {
            mm_mtx.Lock();
            cout << "线程: " << pthread_self() << "已加锁" << endl;
        }
    ~lockGuard() {
        mm_mtx.unlock();
        cout << "线程: " << pthread_self() << "已解锁" << endl;
    }
private:
    Mutex mm_mtx;
};