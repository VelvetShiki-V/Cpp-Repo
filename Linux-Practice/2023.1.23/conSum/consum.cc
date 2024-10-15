#include "consum.hpp"

void* consumer(void* args) {
    Blocking_queue<int>* bq = (Blocking_queue<int>*)args;
    int data = 0;
    while(true) {
        bq->pop(&data);
        cout << "消费者消费: " << data << endl;
        //sleep(1);       // 消费者取数据总是慢于生产者存数据，队列始终保持full
    }
    return nullptr;
}

void* producer(void* args) {
    Blocking_queue<int>* bq = (Blocking_queue<int>*)args;
    int a = 1;
    while(true) {
        bq->push(a);
        ++a;
        cout << "生产者生产: " << a << endl;
        sleep(1);
    }
    return nullptr;
}

int main() {
    pthread_t c, p;
    Blocking_queue<int>* bq = new Blocking_queue<int>();
    pthread_create(&c, nullptr, consumer, (void*)bq);
    pthread_create(&p, nullptr, producer, (void*)bq);
    pthread_join(c, nullptr);
    pthread_join(p, nullptr);
    delete bq;
    return 0;
}