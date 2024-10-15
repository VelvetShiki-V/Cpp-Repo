#ifndef __RINGQUEUE_HPP_
#define __RINGQUEUE_HPP_
#pragma once

#include <iostream>
#include <vector>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "sem.hpp"
using namespace std;

template<class T>
class RingQueue{
public:
    RingQueue(int capacity = 5)     // 初始化工作，将vector初始化，num控制队列大小
    :m_ring_queue(capacity)         // c_sub和p_sub控制生产和消费者在队列中的行进速度（下标走向）
    ,m_num(capacity)                // space_sem和data_sem信号量控制生产和消费者申请和释放空间的顺序，控制同步互斥
    ,c_sub(0)
    ,p_sub(0)
    ,space_sem(capacity)
    ,data_sem(0)
    {
        pthread_mutex_init(&pmtx, nullptr);
        pthread_mutex_init(&cmtx, nullptr);
    }
    ~RingQueue(){
        pthread_mutex_destroy(&pmtx);
        pthread_mutex_destroy(&cmtx);
    }
    void push(const T& in) {        // 生产者向队列推入数据，用生产者下标控制前进顺序，申请空间信号量压入数据后，释放数据信号量使消费者得以消费
        // 1. 先申请信号量，保证多线程将资源先竞争分配
        space_sem.p();
        // 2. 再加锁，保证临界资源仅能同时发配由一个执行流分配任务
        pthread_mutex_lock(&pmtx);
        m_ring_queue[p_sub++] = in;
        p_sub %= m_num;             // 求模以循环在队列中覆盖和使用重复空间，提高空间利用率
        pthread_mutex_unlock(&pmtx);        // 先解锁再释放信号量
        data_sem.v();
    }
    void pop(T* out) {              // 消费者消费数据，用消费者下标控制前进顺序，申请消费数据信号量并获取数据后，释放空间信号量表明生产者可以继续生产数据以覆盖原已消费数据
        data_sem.p();
        pthread_mutex_lock(&cmtx);
        *out = m_ring_queue[c_sub++];
        c_sub %= m_num;
        pthread_mutex_unlock(&cmtx);
        space_sem.v();
    }
private:
    vector<T> m_ring_queue;
    int m_num;
    int c_sub;
    int p_sub;
    Sem space_sem;
    Sem data_sem;
    pthread_mutex_t pmtx;
    pthread_mutex_t cmtx;
};

#endif