#include "TCPServer.hpp"
#include "task.hpp"
#include <memory>

int main() {
    std::unique_ptr<reactor::TCPServer> ptr(new reactor::TCPServer);
    ptr->dispatcher(sentence_reverse);      // 将业务逻辑传入服务器
    return 0;
}