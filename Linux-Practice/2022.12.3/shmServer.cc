#include "shmComm.h"

int main() {
    // 1. 计算key值
    key_t key = ftok(PATH, PJID);
    assert(key != -1);
    Log("项目key值已获取", DEBUG) << "step1, key为, " << hex_trans(key) << endl;
    sleep(10);
    // 2. 创建共享内存段
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | IPC_EXCL | MODE);
    if(shmid == -1) {
        perror("shmget");
        exit(1);
    }
    Log("共享内存段已创建", DEBUG) << "step2" << endl;
    sleep(10);
    // 3. 进程挂接共享内存
    char* addr = (char*)shmat(shmid, nullptr, 0);
    assert(addr != nullptr);
    Log("进程已挂接", DEBUG) << "step3" << endl;
    sleep(10);
    // 4. 与用户端通信
    // ...
    // 5. 进程与共享内存去关联
    int flag = shmdt(addr);
    assert(flag != -1);
    Log("进程已去链接", DEBUG) << "step5" << endl;
    sleep(10);
    // 6. 删除共享内存
    flag = shmctl(shmid, IPC_RMID, nullptr);
    assert(flag != -1);
    (void)flag;
    Log("共享内存已删除", DEBUG) << "step6" << endl;
    return 0;
}