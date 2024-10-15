#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

// 测试硬件信号
void func(int sig) {
    cout << "已接收到信号" << sig << endl;
    sleep(1);
}

int main() {
    signal(SIGSEGV, func);
    int* p = nullptr;
    *p = 1;
    while(true) sleep(1);
    return 0;
}

// // 测试硬件信号
// void func(int sig) {
//     cout << "已接收到信号" << sig << endl;
//     sleep(1);
// }

// int main() {
//     signal(SIGFPE, func);
//     int a = 100;
//     a /= 0;
//     while(true) sleep(1);
//     return 0;
// }

// 测试alarm
// unsigned long count = 0;

// void func(int sig) {
//     cout << count << endl;
//     alarm(1);
// }

// // 测试raise
// int main() {
//     alarm(1);
//     signal(SIGALRM, func);
//     while(true) count++;
//     return 0;
// }


// 模拟kill
// int main(int argc, char* argv[]) {
//     if(argc != 3) {
//         cout << "传入参数错误" << endl;
//         cout << "格式：[./exe] [信号编号] [进程pid]" << endl;
//     }
//     int signal = atoi(argv[1]);     // atoi--convert string to int
//     int procID = atoi(argv[2]);
//     kill(procID, signal);
//     return 0;
// }

// void action(int sig) {
//     cout << "接收到了" << sig << "号信号" << endl;
// }

// 子进程core dump标记位验证
// int main() {
//     pid_t id = fork();
//     if(id == 0) {
//         cout << "子进程pid: " << getpid() << endl;
//         while(true) {
//             sleep(50);
//             int a = 100;
//             a /= 0;
//         }
//         _exit(1);
//     }
//     int status = 0;
//     waitpid(id, &status, 0);
//     cout << "父进程pid: " << getpid() << " 收到的子进程退出信号: " << (status & 0x7F)
//     << " 子进程退出码: " << (WEXITSTATUS(status)) <<" 转储core dump标记位: " << (status >> 7) << endl;
//     return 0;
// }

// 进程异常退出
// int main() {
//     // signal(2, action);      // 回调函数不需要括号和参数，捕捉到信号后自动回调
//     while(true) {
//         cout << "start" << endl;
//         int a = 100;
//         a /= 0;
//         // cout << "pid: " << getpid() << endl;
//         // sleep(1);
//         cout << "end" << endl;
//     }
//     return 0;
// }