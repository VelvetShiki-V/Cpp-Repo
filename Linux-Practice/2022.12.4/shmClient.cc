#include "shmComm.h"

int main() {
    // 1. 获取key值
    key_t key = ftok(PATH, PJID);
    assert(key != -1);
    //sleep(5);
    // 2. 获取已存在的共享内存段
    int shmid = shmget(key, SHM_SIZE, 0);       // 0默认为IPC_CREAT，存在共享内存则返回，没有则创建
    assert(shmid != -1);
    //sleep(5);
    // 2. 用户进程与共享内存挂接
    char* addr = (char*)shmat(shmid, nullptr, 0);
    assert(addr != nullptr);
    //sleep(5);
    // 3. 与服务器端通信——访问控制版本
    int fd = Open_pipe(FIFO_PATH, WRITE);                // 以只写方式打开管道并建立通信
    while(true) {
        ssize_t s = read(0, addr, SHM_SIZE - 1);        // 预留一个位置给'\0'
        if(s > 0) {
            addr[s - 1] = 0;
            Waken(fd);          // 键入数据成功传递至共享区域，唤醒服务端从共享区读取数据
            if(strcmp(addr, "quit") == 0) break;
        }
        cout << endl;
        //sleep(1);
    }
    // 4. 去挂接
    Close_pipe(fd);
    int flag = shmdt(addr);
    assert(flag != -1);
    (void)flag;
    // 客户端不需要删除共享内存段，服务器端负责
    return 0;
}