#include "pool.hpp"

int main() {
    vector<pair<pid_t, int>> subproc;       // 子进程数组，用于存储每个子进程pid和与其对应的父进程写端
    load();
    // 创建多个子进程，并等待接收指令
    for(int i = 0; i < PROCESS_NUMS; ++i) {
        int pipefd[2] = {0};
        int n = pipe(pipefd);
        assert(n == 0);
        (void)n;
        pid_t id = fork();
        assert(id != -1);
        (void)id;
        // 每个子进程执行流
        if(id == 0) {
            close(pipefd[1]);
            while(true) {
                size_t FuncNum = 0;
                ssize_t command = read(pipefd[0], &FuncNum, sizeof(FuncNum));
                if(command > 0 && command < size()) {
                    cout << "子进程pid: " << getpid() << " 开始执行父进程流入指令————";
                    cout << "执行函数编号: " << command << " 执行指令: "
                    << description[command];
                    v[command]();
                }
                else {
                    cout << "非法指令" << endl;
                }
            }
            exit(0);
        }
        // 父进程记录每个子进程pid，并准备派发任务
        close(pipefd[0]);
        subproc.emplace_back(id, pipefd[1]);
    }
    // parent proc
    while(true) {
        srand((unsigned int)time(0));
        size_t randomOrder = rand() % size();
        size_t randomAssignment = rand() % PROCESS_NUMS;
        cout << "父进程: " << getpid() << " 流入管道: " << randomAssignment << " 指令编号: " << randomOrder << endl;
        write(subproc[randomAssignment].second, &randomOrder, sizeof(randomOrder));
        sleep(5);
    }
    for(auto& e: subproc) {
        close(e.second);
    }
    for(auto& k: subproc) {
        waitpid(k.first, nullptr, 0);
    }
    close(3);
    return 0;
}