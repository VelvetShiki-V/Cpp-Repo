#include "udp_server.hpp"

// 服务器使用手册：传入ip和端口号
static void server_usage(std::string proc) {
    std::cout << proc << "port" << std::endl;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        server_usage(argv[0]);
        exit(1);
    }
    // 1. 填入待通信客户端主机IP和端口号，使用智能指针管理服务器类（封装）
    uint16_t port = atoi(argv[1]);
    std::unique_ptr<UdpServer> p(new UdpServer(port));

    // 2. 将UDP服务器初始化（填充IP和端口号字段）并绑定（特定进程）
    p->init();

    // 3. 准备接收客户端讯息并予以反馈
    p->start();
    return 0;
}