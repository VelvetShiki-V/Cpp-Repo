#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<vector>
using namespace std;

typedef void (*handler_t)();
vector<handler_t> handlers;
void func1() {
    cout << "tmp proc1" << endl;
}
void func2() {
    cout << "tmp func2" << endl;
}

void load() {
    handlers.push_back(func1);
    handlers.push_back(func2);
}

int main() {
    pid_t id = fork();
    if (id < 0) {
        cout << "子进程创建失败，程序退出" << endl;
        exit(-1);
    }
    else if (id == 0) {
       int count = 5;
       while(count) {
           cout << "child proc" << "pid :" << getpid() << "ppid :" << getppid() << endl;
          count--;
          sleep(1);
       }
       exit(1);
    }
    else {
        cout << "parent proc" << "pid : " << getpid() << "ppid : " << getppid() << endl;
        int quit = 0;
        while(!quit) {
            int status = 0;
            pid_t ret = waitpid(-1, &status, WNOHANG);
            if (ret > 0) {
                cout << "等待子进程成功，退出码为 : " << WEXITSTATUS(status) << endl;
                quit = 1;
            }
            else if (ret == 0) {
                cout << "子进程尚未退出，父进程可继续执行Load任务" << endl;
                if(handlers.empty()) {
                    load();
                }
                for(auto e: handlers) {
                    e();
                }
            }
            else {
                cout << "等待子进程失败" << endl;
                quit = 1;
            }
            sleep(1);
        }
    }
    return 0;
}
