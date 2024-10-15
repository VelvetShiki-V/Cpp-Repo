#include "pipe.hpp"

int main() {
    int fd = open(PATH.c_str(), O_WRONLY);      // 客户端对命名管道只负责数据输入
    if(fd < 0) {
        perror("open");
        exit(1);
    }
    string Buffer;
    while(true) {
        cout << "client Shiki:> ";
        getline(cin, Buffer);           // 输入的数据可以空格，以string类型传输
        ssize_t n = write(fd, Buffer.c_str(), Buffer.size());
        if(n < 0) {
            cerr << "写入失败" << endl;
            break;
        }
    }
    close(fd);
    return 0;
}