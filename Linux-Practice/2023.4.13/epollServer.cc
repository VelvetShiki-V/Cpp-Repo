#include "epollServer.hpp"
#include <memory>

void read_handler(const string s) {
    std::cout << s << std::endl;
}

int main() {
    std::unique_ptr<epoll_server::EpollServer> ptr(new epoll_server::EpollServer(read_handler));
    ptr->run();
    return 0;
}