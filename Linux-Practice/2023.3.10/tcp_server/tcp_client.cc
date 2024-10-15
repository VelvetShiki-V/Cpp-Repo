#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <cstring>
#include <cassert>
#include <unistd.h>
#define SIZE 1024

static void client_usage(std::string proc) {
    std::cout << proc << " ip port" << std::endl;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        client_usage(argv[0]);
        exit(0);
    }
    std::string server_ip = argv[1];
    uint16_t server_port = atoi(argv[2]);

    // 客户端建立服务器连接三板斧：1. 创建socket套接字   2. 选择网络服务种类sockaddr  3. connect与目标服务器建立连接并
    int toServer_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(toServer_sock < 0) {
        std::cout << "socket创建失败" << std::endl;
        exit(1);
    }
    sockaddr_in send_service;
    bzero(&send_service, sizeof send_service);
    send_service.sin_addr.s_addr = inet_addr(server_ip.c_str());
    send_service.sin_port = htons(server_port);
    send_service.sin_family = AF_INET;
    int flag = connect(toServer_sock, (sockaddr*)&send_service, sizeof send_service);
    assert(flag != -1);

    // 准备与服务器IO通信，响应式服务器实现数据发收，使用send代替write，recv代替read即可
    while(true) {
        std::cout << "#client: ";
        std::string sendMessage;
        char buf[SIZE];
        std::getline(std::cin, sendMessage);
        if(sendMessage == "quit") break;
        ssize_t t = send(toServer_sock, sendMessage.c_str(), sendMessage.size(), 0);
        assert(t != -1);
        ssize_t r = recv(toServer_sock, buf, sizeof(buf)-1, 0);
        buf[r] = 0;
        std::cout << "server: " << buf << std::endl;
    }
    close(toServer_sock);
    return 0;
}