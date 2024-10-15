#include "tcp_server.hpp"

static void server_usage(const std::string proc) {
    std::cout << proc << " port" << std::endl;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        server_usage(argv[0]);
        exit(1);
    }
    uint16_t port = atoi(argv[1]);
    std::unique_ptr<TcpServer> sptr(new TcpServer(port));       // 智能指针保证服务器对象能被自动释放
    sptr->init();
    sptr->start();
    return 0;
}