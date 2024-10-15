#pragma once
#include <iostream>
#include <pthread.h>
#include <queue>
#include <mutex>
#include <unistd.h>
#include <ctime>
#include "lockGuard.hpp"
using namespace std;

template<class T>
class Blocking_queue{
public:
    Blocking_queue(int capacity = 6)
    :m_capacity(capacity)       // 锁和条件变量初始化
    {
        pthread_mutex_init(&m_mtx, nullptr);
        pthread_cond_init(&full, nullptr);
        pthread_cond_init(&empty, nullptr);
    }
    ~Blocking_queue() {         // 销毁锁和条件变量
        pthread_mutex_destroy(&m_mtx);
        pthread_cond_destroy(&full);
        pthread_cond_destroy(&empty);
    }
    void push(const T& data) {  // 生产者产数据——队列入队
        lockGuard lock(&m_mtx);
        while(isFull()) pthread_cond_wait(&full, &m_mtx);       // while判断以保证该线程被唤醒时不是伪唤醒
        q.push(data);                                         // 而是确保压入数据时队列不满，并一定可以push
        // if(q.size() >= m_capacity/2) pthread_cond_signal(empty);   生产优化
        pthread_cond_signal(&empty);     // 唤醒空队列线程(消费者)准备取数据
    }
    void pop(T* data) {                  // 消费者取数据——队列出队
        lockGuard lock(&m_mtx);
        while(isEmpty()) pthread_cond_wait(&empty, &m_mtx);
        *data = q.front();              // 出队前将队头元素取出给消费者线程，再出队
        q.pop();
        pthread_cond_signal(&full);      // 唤醒满队列线程(生产者)准备推数据
    }
private:
    bool isEmpty() {            // 判断队列已满或空
        return q.size() == 0;
    }
    bool isFull() {
        return q.size() == m_capacity;
    }
private:
    queue<T> q;                 // 填充数据的队列缓冲区
    int m_capacity;             // 队列容量
    pthread_mutex_t m_mtx;     // 线程互斥锁
    pthread_cond_t full;       // 条件变量——满
    pthread_cond_t empty;      // 条件变量——空
};

int add(int a, int b) {
    return a + b;
}