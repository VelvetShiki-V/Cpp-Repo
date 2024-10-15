#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

int flag = 0;

void handler(int sig) {
    (void)sig;
    cout << "接收到信号: " << sig << endl;
    flag = 1;
    cout << "flag置为1, 程序将退出" << endl;
}

int main() {
    signal(2, handler);
    while(!flag);
    cout << "进程退出" << endl;
    return 0;
}
