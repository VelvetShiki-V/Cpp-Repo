#include "ringQueue.hpp"

void* consumer(void* args) {
    RingQueue<int>* rq = (RingQueue<int>*)args;
    int x = 0;
    while(true) {
        sleep(1);
        rq->pop(&x);
        cout << "[" << pthread_self() << "]" << "消费了" << x << endl;
    }
}

void* producer(void* args) {
    RingQueue<int>* rq = (RingQueue<int>*)args;
    while(true) {
       // sleep(1);
        int x = rand() % 100;
        rq->push(x);
        cout << "[" << pthread_self() << "]" <<  "生产了" << x << endl;
    }
}

int main() {
    pthread_t c[3], p[2];
    srand((uint64_t)nullptr);
    RingQueue<int>* rq = new RingQueue<int>();
    pthread_create(c, nullptr, consumer, (void*)rq);
    pthread_create(c + 1, nullptr, consumer, (void*)rq);
    pthread_create(c + 2, nullptr, consumer, (void*)rq);
    pthread_create(p, nullptr, producer, (void*)rq);
    pthread_create(p + 1, nullptr, producer, (void*)rq);
    for(int i = 0; i < 3; ++i) pthread_join(c[i], nullptr);
    for(int i = 0; i < 2; ++i) pthread_join(p[i], nullptr);
    delete rq;
    return 0;
}