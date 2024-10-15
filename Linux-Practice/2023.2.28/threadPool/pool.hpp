#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>
using namespace std;

typedef void*(func_t)(void*);

class Thread{
public:
    Thread(int num) {
        thread_name = "thread-" + num;
    }
    void start(func_t callback, void* args) {
        pthread_create(&tid, nullptr, callback, args);
    }
    void join() {
        pthread_join(tid, nullptr);
    }
private:
    pthread_t tid;
    string thread_name;
    func_t func;

};