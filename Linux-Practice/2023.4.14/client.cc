#include "protocol.hpp"
#include "sock.hpp"
#include <cassert>
#include <iostream>
#include <string>
using namespace std;

int main() {
    // 1. 客户端创建套接字
    string ip = "127.0.0.1";
    uint16_t port = 8080;
    int service_sock = Sock::socket_create();
    // 2. 使用本地环回地址127.0.0.1在本地网络服务器内部测试
    // connect让sock与ip和OS自动选择的空闲port绑定，因为本地环回测试，在本机上测试网络服务的服务器都能接收到该客户端通过本地广播处的信息
    if(!Sock::connect_to_server(service_sock, ip, port)) assert(false);
    while(true) {
        // 3. 业务处理——反转单词，先输入待测试句子或单词
        cerr << "client# ";
        string input;
        getline(cin, input);
        // 4. 先序列化数据，再加协议首尾
        Request rq;
        rq.serialize(input);
        if(!encode(input)) {
            cerr << "输入数据非法" << endl;     // 差错处理，不接受空白输入
            continue;
        }
        // 5. 数据广播本地网络
        Sock::msg_send(service_sock, input);
        string output;
        // 6. 接收到服务器响应报文
        output = Sock::msg_get(service_sock);
        vector<string> vget;
        // 7. 解析数据，反序列化得到数据
        decode(output, vget);
        Response rp;
        rp.deserialize(vget[0]);
        cout << "server responds# ";
        // 8. 得到结果
        cout << vget[0] << endl;
        cout << endl;
    }
}