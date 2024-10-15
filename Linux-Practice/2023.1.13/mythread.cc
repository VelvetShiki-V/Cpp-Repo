#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

// 多线程加锁抢座位
#define THREAD_NUM 5
int g_seatsNum = 10000;

class Thread_data{
public:
    Thread_data(const string& name, pthread_mutex_t* mtx)
        :pname(name)
        ,pmtx(mtx)
        {}
public:
    string pname;
    pthread_mutex_t* pmtx;
};

void* ThreadFunc(void* args) {
    Thread_data* td = (Thread_data*)args;
    while(true) {
        pthread_mutex_lock(td->pmtx);
        if(g_seatsNum > 0) {
            usleep(1000);
            cout << td->pname << "抢走了" << g_seatsNum << endl;
            g_seatsNum--;
            pthread_mutex_unlock(td->pmtx);
        }
        else {
            pthread_mutex_unlock(td->pmtx);
            break;
        }
    }
    delete td;
    return nullptr;
}

int main() {
    pthread_t tid[THREAD_NUM];
    pthread_mutex_t mtx;
    pthread_mutex_init(&mtx, nullptr);
    for(int i = 0; i < THREAD_NUM; ++i) {
        Thread_data* t = new Thread_data("thread-", &mtx);
        t->pname += to_string(i);
        pthread_create(tid + i, nullptr, ThreadFunc, (void*)t);
    }
    for(int i = 0; i < THREAD_NUM; ++i) {
        pthread_join(tid[i], nullptr);
        cout << "主线程回收了"<< tid[i] << endl;
    }
    pthread_mutex_destroy(&mtx);
    return 0;
}

// 线程分离并异常终止
// void* threadFunc(void* arg) {
//     pthread_detach(pthread_self());
//     int n = 5;
//     while (n--) {
//         cout << (char*)arg << "运行中..." << endl;
//         sleep(1);
//     }
//     int a = 10;
//     a /= 0;
//     pthread_exit((void*)11);
// }

// int main() {
//     pthread_t tid;
// 	pthread_create(&tid, nullptr, threadFunc, (void*)"thread-1: ");
//     cout << "主线程运行中..." << endl;
//     while(true) sleep(1);
// 	return 0;
// }

// 全局数据区所有线程共享
// __thread int g_val;
// void* threadFunc(void* arg) {
//     while (true) {
//         cout << (char *)arg << pthread_self() << "读取到全局变量: " << g_val << endl;
//         g_val++;
//         sleep(1);
//     }
//     return nullptr;
// }

// int main() {
//     pthread_t tid;
// 	pthread_create(&tid, nullptr, threadFunc, (void*)"thread-1: ");
//     while(true) {
//         cout << "主线程tid: " << pthread_self() << "读取到全局变量: " << g_val << endl;
//         sleep(1);
//     }
//     pthread_join(tid, nullptr);
// 	return 0;
// }

// 线程tid是地址
// void* threadFunc(void* arg) {
//     return nullptr;
// }

// int main() {
//     pthread_t tid;
// 	pthread_create(&tid, nullptr, threadFunc, (void*)"thread-1");
//     printf("tid: %lu \n %p\n", tid, tid);
// 	return 0;
// }