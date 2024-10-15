#include "pool.hpp"

int main() {
    vector<pair<pid_t, int>> subproc;       // 子进程数组，用于存储每个子进程pid和与其对应的父进程写端端口
    load();     // 将任务接口加载到进程池中
    // 创建多个子进程，并等待接收指令
    for(int i = 0; i < PROCESS_NUMS; ++i) {
        int pipefd[2] = {0};        // 父进程多开管道文件，与每个子进程读端形成1对多数据共享
        int n = pipe(pipefd);
        assert(n == 0);
        (void)n;
        pid_t id = fork();          // fork子进程，由每个子进程等待父端指令流入并执行特定任务
        assert(id != -1);
        (void)id;
        // 每个子进程执行流，子进程数量宏定义于头文件中PROCESS_NUMS
        if(id == 0) {
            close(pipefd[1]);       // 管道是单向通信，子关闭写端，父关闭读端
            while(true) {
                // order接收父端写入的指令数据，flag用于检测接收是否正常，若父端关闭则置0退出子进程，若读取失败置-1
                size_t order = 0;
                ssize_t flag = read(pipefd[0], &order, sizeof(order));
                assert(flag != -1);
                if(flag == 0) break;
                if(order >= 0 && order < size()) {
                    cout << "子进程pid: " << getpid() << " 开始执行父进程流入指令————";
                    cout << "执行函数编号: " << order << " 执行指令: "
                    << description[order];      // description哈希表用于描述接收到的为何种指令，数组v用于开始执行某个具体指令
                    v[order]();
                }
                else {
                    cout << "非法指令" << endl;
                }
            }
            cout << "子进程: " << getpid() << "读端关闭成功" << endl;
            exit(0);
        }
        // 父进程记录每个子进程pid，并准备派发任务
        close(pipefd[0]);
        subproc.emplace_back(id, pipefd[1]);
    }
    // parent proc
    int cnt = 1;
    while(true) {
        if(cnt == 6) break;     // 父进程分配5次任务后关闭写端，此时子进程应该根据父进程写端关闭状态来自动关闭读端(由read检测)
        cout << "父进程执行第" << cnt++ << "次管道数据流入" << endl;
        srand((unsigned int)time(0));
        size_t randomOrder = rand() % size();       // 随机分配任务
        size_t randomAssignment = rand() % PROCESS_NUMS;        // 随机分配需要执行任务的进程
        cout << "父进程: " << getpid() << " 流入管道: " << randomAssignment << " 指令编号: " << randomOrder << endl;
        // 将任务从某个父进程写端端口写入连通的管道，并由数组的每个写端间接对应的子进程读端read获取到，并执行对应任务
        int ret = write(subproc[randomAssignment].second, &randomOrder, sizeof(randomOrder));
        assert(ret != -1);
        (void)ret;
        sleep(3);
    }
    // 关闭父进程对每个管道的写端——自动关闭子进程读端
    for(int i = 0; i < subproc.size(); ++i) {
        close(subproc[i].second);
        cout << "父进程: " << getpid() << "写端" << i + 1 << "关闭成功" << endl;
    }
    // 子进程读端关闭——自动结束子进程，父进程等待回收
    for(auto& e: subproc) {
        waitpid(e.first, nullptr, 0);
        cout << "等待子进程: " << e.first << "成功" << endl;
    }
    return 0;
}