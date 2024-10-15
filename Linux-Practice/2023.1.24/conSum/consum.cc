#include "consum.hpp"
#include "task.hpp"

void* consumer(void* args) {
    Blocking_queue<Task>* bq = (Blocking_queue<Task>*)args;

    while(true) {
        // 1. 获取任务
        Task t;
        // 2. 执行任务
        bq->pop(&t);
        cout << pthread_self() << "消费者执行结果: " << t() << endl << endl;;
        sleep(1);             // 消费者取数据总是慢于生产者存数据，队列始终保持full
    }
    return nullptr;
}

void *producer(void *args)
{
    Blocking_queue<Task> *bq = (Blocking_queue<Task> *)args;
    // 2. 推送任务
    while (true) {
        // 1. 生产任务
        int x = rand() % 100;
        usleep(rand()%1000);
        int y = rand() % 100;
        Task t(x, y, add);  
        bq->push(t);
        cout << x << "+" << y << " = ?" << endl;
        sleep(1);
    }
    return nullptr;
}

int main() {
    srand(time(nullptr));
    pthread_t cons[2];
    pthread_t pros[2];
    Blocking_queue<Task>* bq = new Blocking_queue<Task>();
    pthread_create(cons, nullptr, consumer, (void*)bq);
    pthread_create(cons + 1, nullptr, consumer, (void*)bq);
    pthread_create(pros, nullptr, producer, (void*)bq);
    pthread_create(pros + 1, nullptr, producer, (void*)bq);
    pthread_join(cons[0], nullptr);
    pthread_join(cons[1], nullptr);
    pthread_join(pros[0], nullptr);
    pthread_join(pros[1], nullptr);
    delete bq;
    return 0;
}