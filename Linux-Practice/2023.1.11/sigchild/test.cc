#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

void handler(int sig) {
    cout << "父进程接收到信号: " << sig << endl;
    int status;
    waitpid(-1, &status, WNOHANG);      // 父进程非阻塞等待子进程退出
    cout << "子进程已退出" << endl;
    // exit(1); 此处不能使用exit，因为handler方法执行者是父进程，将使父进程本身退出
}

// 父进程显示忽略子进程退出信号，由OS回收
int main() {
    pid_t id = fork();
    signal(SIGCHLD, handler);
    if(id == 0) {
        cout << "子进程pid: " << getpid() << endl;
        sleep(100);
        exit(1);       
    }
    while(true) {
        cout << "父进程pid: " << getpid() << endl;
        sleep(1);
    }
    return 0;
}

// 父进程非阻塞等待子进程退出，接收退出信号
// void handler(int sig) {
//     cout << "父进程接收到信号: " << sig << endl;
//     int status;
//     waitpid(-1, &status, WNOHANG);      // 父进程非阻塞等待子进程退出
//     cout << "子进程已退出" << endl;
//     // exit(1); 此处不能使用exit，因为handler方法执行者是父进程，将使父进程本身退出
// }

// int main() {
//     pid_t id = fork();
//     signal(SIGCHLD, handler);
//     if(id == 0) {
//         cout << "子进程pid: " << getpid() << endl;
//         sleep(3);
//         exit(1);        // 子进程3秒后将退出
//     }
//     while(true) {
//         cout << "父进程pid: " << getpid() << endl;
//         sleep(1);
//     }
//     return 0;
// }