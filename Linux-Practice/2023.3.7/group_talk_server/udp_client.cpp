#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <memory>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "log.hpp"
#include "thread.hpp"
#define SIZE 1024

static std::string server_ip;
static std::string server_port;

void* send(void* args) {
    // 传入sock因为recvfrom将要使用到socket提供的文件描述符进行IO
    int sock = *(int*)(ThreadData*)args;
    // sockaddr任务属性用于发送数据
    sockaddr_in cli_send;
    bzero(&cli_send, sizeof cli_send);
    cli_send.sin_family = AF_INET;
    cli_send.sin_addr.s_addr = inet_addr(server_ip.c_str());
    cli_send.sin_port = htons(atoi(server_port.c_str()));
    while(true) {
        std::cerr << "#client: ";       // 必须用cerr，否则将显示结果到输出管道文件中
        std::string output;
        std::getline(std::cin, output);
        if(output == "quit") break;
        ssize_t t = sendto(sock, output.c_str(), output.size(), 0, (sockaddr*)&cli_send, sizeof cli_send);
        if(t < 0) {
            std::cout << "sending fail" << std::endl;
            break;
        }
    }
    return nullptr;
}

void* recv(void* args) {
    // 传入sock因为recvfrom将要使用到socket提供的文件描述符进行IO
    int sock = *(int*)(ThreadData*)args;
    // sockaddr任务属性用于接收数据
    sockaddr_in cli_recv;
    socklen_t len = sizeof cli_recv;
    char buf[SIZE];
    while(true) {
        bzero(buf, sizeof buf);     // 每次重读数据需要清空缓冲区，否则数据将会重叠
        ssize_t t = recvfrom(sock, buf, sizeof buf, 0, (sockaddr*)&cli_recv, &len);
        if(t > 0) {
            buf[t] = 0;
            std::cout << buf << std::endl;
        }
        else break;
    }
}

// 客户端使用手册：传入ip和端口号
void client_usage(std::string proc) {
    std::cout << proc << " ip " << "port" << std::endl;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        client_usage(argv[0]);
        exit(1);
    }
    // 1. 创建网络通信套接字，填充需要通信的服务器Ip和端口号
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd < 0) exit(2);
    // 将服务器IP和端口全局化，使不同线程共享（只读数据是安全的）
    server_ip = argv[1];
    server_port = argv[2];
    // 2. 初始化并启动线程，分别对服务器执行收发功能（全双工，不会竞争临界资源socket）
    Thread sender(1, (void*)&fd, send);
    Thread recver(2, (void*)&fd, recv);
    sender.start();
    recver.start();
    // 3. 回收线程并关闭socket
    sender.join();
    recver.join();

    close(fd);
    return 0;
}