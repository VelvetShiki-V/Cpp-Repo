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
#define SIZE 1024

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
    sockaddr_in client;     // 套接字属性填充结构体，其中包含客户端需要[发送]给服务器的ip和端口
    socklen_t len = sizeof client;
    bzero(&client, sizeof client);      // 初始化
    client.sin_addr.s_addr = inet_addr(argv[1]);        // 将待通信主机的IP和端口号填充套接字中（注意网络大端规则和4字节ip规范）
    client.sin_port = htons(atoi(argv[2]));
    client.sin_family = AF_INET;
    
    // 2. 无需手动绑定客户端口号（系统自动寻找空闲主机端口号并在第一次发送数据过去时完成绑定）
    std::string output;
    logMessage(DEBUG, "ready to communicate with server ip[%d] port[%d]", client.sin_addr.s_addr, client.sin_port);
    char buf[SIZE];
    while(true) {
        // 3. 手动输入数据以传输给服务器主机sendto
        std::cout << "#client: ";
        std::getline(std::cin, output);
        if(output == "quit") break;
        logMessage(DEBUG, "data input: %s status: %s", output.c_str(), strerror(errno));
        ssize_t s = sendto(fd, output.c_str(), output.size(), 0, (sockaddr*)&client, sizeof client);
        if(s < 0) {
            logMessage(FATAL, "message sending status: %s", strerror(errno));
            break;
        }

        // 4. 响应式服务器主机，数据原封返回，创建新的套接字以实现此功能
        sockaddr_in temp;       // 不能直接使用上述定义的client套接字吗？
        socklen_t lent = sizeof temp;
        ssize_t input = recvfrom(fd, buf, sizeof buf, 0, (sockaddr*)&temp, &lent);
        if(input > 0) {
            buf[input] = 0;
            printf("server echos: %s\n", buf);
        }
    }
    close(fd);
    return 0;
}