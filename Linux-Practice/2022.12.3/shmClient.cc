#include "shmComm.h"

int main() {
    // 1. 获取key值
    key_t key = ftok(PATH, PJID);
    assert(key != -1);
    sleep(5);
    // 2. 获取已存在的共享内存段
    int shmid = shmget(key, SHM_SIZE, 0);       // 0默认为IPC_CREAT，存在共享内存则返回，没有则创建
    assert(shmid != -1);
    sleep(5);
    // 2. 用户进程与共享内存挂接
    char* addr = (char*)shmat(shmid, nullptr, 0);
    assert(addr != nullptr);
    sleep(5);
    // 3. 与服务器端通信
    // 4. 去挂接
    int flag = shmdt(addr);
    assert(flag != -1);
    (void)flag;
    // 客户端不需要删除共享内存段，服务器端负责
    return 0;
}