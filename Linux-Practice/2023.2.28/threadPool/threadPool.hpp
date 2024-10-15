#include "pool.hpp"

class ThreadPool{
public:
    ThreadPool(){}
    ~ThreadPool(){}
    void run(){}
    void taskPush(){}
private:
    vector<Thread*> threads;
    int num;
};