#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "sock.hpp"
#include "protocol.hpp"

static void client_usage(const char* proc) {
    std::cout << proc << " ip port" << std::endl;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        client_usage(argv[0]);
        exit(1);
    }
    // 1. 创建套接字并建立tcp连接
    Sock socket;
    int sockfd = socket.sock_create();
    std::string server_ip = argv[1];
    std::string server_port = argv[2];
    socket.CSconnet(sockfd, server_ip, server_port);

    while(true) {
        // 2. 输入数值运算
        int x, y;
        char operation;
        std::cerr << "format: x op y" << std::endl << "#input: " << std::endl;
        std::cin >> x >> operation >> y;

        // 3. 将待运算数值序列化，加上协议报头并传输给服务器
        Request rq;
        std::string str = rq.serialize(x, y, operation);
        // std::cerr << "debug: json serialize: " << str << std::endl;
        encode(str);
        // std::cerr << "debug: encode--" << str << std::endl;
        Send(str, sockfd);

        // 4. 服务器处理完毕将序列化数值解码验证，反序列化得到结果
        Response rp;
        std::string getfrom = Recv(sockfd);
        std::string result;
        while(result.empty()) {
            result = decode(getfrom);
        }
        // std::cerr << "debug: decode--" << result << std::endl;
        rp.deserialize(result);
        std::cerr << "result: " << rp.result << " status: " << err_info[rp.errnum] << std::endl << std::endl;
    }

    return 0;
}