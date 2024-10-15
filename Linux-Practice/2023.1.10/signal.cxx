#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

void showPending(sigset_t* pd) {
    for(int i = 1; i <= 31; ++i) {
        cout << sigismember(pd, i);		// 打印该进程的pending信号集
        }
    cout << endl;
}
void handler(int sig) {
    cout << "捕捉到信号: " << sig << endl;
    int count = 20;
    sigset_t pd;
    sigemptyset(&pd);
    while(true){
        sigpending(&pd);
        showPending(&pd);
        sleep(1);
        count--;
        if(!count) {		// 当计数器间隔20s后，将完成对2号信号的handler处理，转而继续处理其他在pending中的信号
            break;
        }
    }
}
int main() {
    cout << "当前进程pid: " << getpid() << endl;
    struct sigaction act, oact;		// sigaction类型是一个结构体，其中包含对信号的处理回调函数和mask屏蔽掩码
    act.sa_flags = 0;				// flag用于处理实时信号，该实验不关心
    act.sa_handler = handler;		// 回调函数，将调用用户自定义信号捕获回调方法
    sigemptyset(&act.sa_mask);      // 信号掩码初始化
    sigaddset(&act.sa_mask, 3);     // 将其他处理中信号屏蔽加入BLOCK信号屏蔽字中
    sigaddset(&act.sa_mask, 4);
    sigaddset(&act.sa_mask, 5);
    sigaddset(&act.sa_mask, 6);
    sigaddset(&act.sa_mask, 7);
    // 信号捕捉处理
    sigaction(2, &act, &oact);		// 将回调方法和屏蔽字段填入信号捕获的该进程中
    while(true) sleep(1);
    return 0;
}