#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
using namespace std;

// 线程返回结果给主线程
void* threadFunc(void* args) {
    cout << "线程1创建成功, 接收到参数为: " << (char*)args << endl;
    cout << "线程1运行中..." << endl;
    int count = 5;
    while(count--) {
        sleep(1);
    }
    char* alphabet = new char[26];
    for(int i = 0; i < 26; ++i) {
        alphabet[i] = i + 65;
    }
    return (void*)alphabet;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, nullptr, threadFunc, (void*)"thread-1");       // 创建新线程
    int count = 2;
    cout << "主线程运行中..." << endl;
    while(count--) {
        sleep(1);
    }
    cout << "主线程等待回收线程1中..." << endl;  
    char* ret = nullptr;
    pthread_join(tid, (void**)&ret);        // 主线程阻塞等待回收创建的线程
    for(int i = 0; i < 26; ++i) {
        cout << ret[i] << " ";
    }
    cout << endl;
    cout << "主线程等待线程1成功" << endl;
    return 0;
}


// 创建线程，等待线程
// void* threadFunc(void* args) {
//     cout << "线程1创建成功, 接收到参数为: " << (char*)args << endl;
//     int count = 10;
//     while(count--) {
//         cout << "线程1运行中..." << endl;
//         sleep(1);
//     }
//     return (void*)5;        // 返回值设置为整型，强转为对应void*类型返回
// }

// int main() {
//     pthread_t tid;
//     pthread_create(&tid, nullptr, threadFunc, (void*)"thread-1");       // 创建新线程
//     int count = 5;
//     while(count--) {
//         cout << "主线程运行中..." << endl;
//         sleep(1);
//     }
//     cout << "主线程等待回收线程1中..." << endl;  
//     void* ret = nullptr;
//     pthread_join(tid, &ret);        // 主线程阻塞等待回收创建的线程
//     cout << "主线程等待线程1成功，退出码:" << (long long)ret << endl;
//     return 0;
// }