#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
using namespace std;

void* threadFunc(void* arg) {
    const string name = (char*)arg;
    while(true) {
        cout << name << "的pid: " << getpid() << '\n' << endl;
        sleep(1);
    }
}

int main() {
    pthread_t tid[5];
    char name[32];
    for(int i = 0; i < 5; ++i) {
        snprintf(name, sizeof name, "%s-%d", "thread", i);
        pthread_create(tid + i, nullptr, threadFunc, name);
        sleep(1);
    }
    while(true)  {
        cout << "---------------------------------" << endl;
        cout << "主线程pid: " << getpid() << endl;
        sleep(3);
    }
    return 0;
}