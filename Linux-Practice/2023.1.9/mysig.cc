#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
using namespace std;

static void showpending(sigset_t& pdset) {
    for(int i = 1; i < 32; ++i) {
        cout << sigismember(&pdset, i);     // 循环打印pending位图的每个信号位
        fflush(stdout);     // 强制刷新，否则将执行全缓冲
    }
    cout << endl;
    sleep(1);
}

static void block(int num) {
    sigset_t sig;
    sigemptyset(&sig);
    sigaddset(&sig, num);
    int flag = sigprocmask(SIG_BLOCK, &sig, nullptr);
    assert(flag == 0);
    (void)flag;
    sigpending(&sig);
    showpending(sig);
}

// 信号全部屏蔽测试
int main() {
    for(int i = 1; i <= 31; ++i) {
        block(i);
    }
    return 0;
}

// void handler(int sig) {
//     cout << "接收到信号: " << sig << " 信号已递达，未决态消除" << endl;
// }

// // pending&block信号屏蔽测试
// int main() {
//     signal(2, handler);
//     sigset_t pending, set, oset;
//     sigemptyset(&pending);             // 信号位图初始化
//     sigemptyset(&set);
//     sigemptyset(&oset);
//     sigaddset(&set, SIGINT);          // 屏蔽2号信号，2号信号为键盘组合键ctrl c以终止进程
//     sigprocmask(SIG_BLOCK, &set, &oset);        // 将屏蔽2号的位图写入进程block屏蔽字中
//     cout << "2号信号屏蔽成功" << endl;
//     int count = 0;
//     while(true) {
//         sigpending(&pending);
//         showpending(pending);       // 如果没发送2号信号，则pending表不会改变，发送则可以看到2号位置1
//         ++count;
//         if(count == 15) {
//             cout << "解除屏蔽" << endl;
//             int flag = sigprocmask(SIG_SETMASK, &oset, nullptr);
//             assert(flag == 0);
//             (void)flag;
//         }
//     }
//     return 0;
// }


// kill -9管理员信号测试
// void handler(int sig) {
//     cout << "接收到信号: " << sig << endl;
// }

// int main() {
//     for(int i = 0; i < 32; ++i) signal(i, handler);
//     while(true) sleep(1);
//     return 0;
// }