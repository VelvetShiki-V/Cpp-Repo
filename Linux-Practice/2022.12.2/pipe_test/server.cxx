#include "pipe.hpp"

static void getMessage(int fd) {        // 子进程接收管道文件数据
    char Buffer[SIZE];
    while(true) {
        memset(Buffer, '\0', sizeof(Buffer));       // 将缓冲区数据置空，read后空出1个字节存储结束符'\0'
        ssize_t n = read(fd, Buffer, sizeof(Buffer) - 1);
        if(n > 0) {         // 从管道中读取成功，输出客户端输入的信息，并阻塞等待用户输入
            cout << "Server[" << getpid() << "] receives: " << Buffer << endl;
        }
        else if(n == 0) {   // 否则输出错误信息并exit关闭该子进程
            cerr << getpid() << " ";
            Log("读取结束，用户写端关闭，服务器读端关闭\n", NOTICE);
            break;
        }
        else {
            cerr << getpid();
            Log("读取失败\n", ERROR);
            break;
        }
    }
}

int main() {
    int ret = mkfifo(PATH.c_str(), MODE);       // 服务器端开启，创建命名管道文件(带路径和权限)
    if(ret < 0) {
        perror("mkfifo");
        exit(1);
    }
    Log("创建管道文件成功", DEBUG) << " step 1" << endl;        // 日志记录信息(打印版本)
    int fd = open(PATH.c_str(), O_RDONLY);
    if(fd < 0) {
        perror("open");
        exit(2);
    }
    Log("管道文件打开成功", DEBUG) << " step 2" << endl;
    for(int i = 0; i < CHILDNUMS; ++i) {
        pid_t id = fork();      // 创建子进程并让子进程阻塞等待接收打印用户数据
        if(id == 0) {
            getMessage(fd);
            exit(3);
        }
    }
    for(int i = 0; i < CHILDNUMS; ++i) {        // 进程等待
        pid_t p = waitpid(-1, nullptr, 0);
        if(p < 0) {
            Log("子进程等待失败\n", ERROR);
        }
    }
    close(fd);
    Log("管道已关闭\n", NOTICE);
    unlink(PATH.c_str());
    Log("管道文件已删除\n", WARNING);
    return 0;
}