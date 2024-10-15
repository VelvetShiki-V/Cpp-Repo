#include "tcp_server.hpp"

static void server_usage(const char* proc) {
    std::cout << "usage: " << proc << " port" << std::endl;
}

// 数值计算规则
static Response calculation(const Request& rq) {
    int result;
    Response rp;
    logMessage(DEBUG, "将要计算%d %c %d", rq.m_x, rq.m_op, rq.m_y);
    switch(rq.m_op) {
        case '+': rp.result = rq.m_x + rq.m_y;
            break;
        case '-': rp.result = rq.m_x - rq.m_y;
            break;
        case '*': rp.result = rq.m_x * rq.m_y;
            break;
        case '/': {
            if(rq.m_y == 0) {rp.errnum = 1; logMessage(ERROR, "%s", err_info[rp.errnum]);}
            else rp.result = rq.m_x / rq.m_y;
        }
            break;
        case '%': {
            if(rq.m_y == 0) {rp.errnum = 1; logMessage(ERROR, "%s", err_info[rp.errnum]);}
            else rp.result = rq.m_x % rq.m_y;
        }
            break;
        default: {rp.errnum = 2; logMessage(ERROR, "%s", err_info[rp.errnum]);}
            break;
    }
    return rp;
}

// 线程运行回调任务（计算）
void calculator(int sock) {
    while(true) {
        // 1. 线程执行，先从service_sock接收来自客户端的数据——序列化数值
        std::string get = Recv(sock);
        if(get.empty()) {
            logMessage(ERROR, "no data obtained, current task quit");       // 客户端关闭，服务器检测后继续运行（保证）
            break;
        }
        logMessage(NORMAL, "dataset obtained and ready to handle");
        Request rq;
        // 2. 对收到的数据进行解码，验证数据完整性
        std::string str = decode(get);
        if(str.empty()) {
            logMessage(ERROR, "接收数据不完整，等待继续接收");
            continue;
        }
        logMessage(DEBUG, "decode: %s", str.c_str());
        // 3. 将完整收到的数据反序列化，并进行计算
        rq.deserialize(str);
        logMessage(DEBUG, "x = %d, op = %c, y = %d", rq.m_x, rq.m_op, rq.m_y);
        Response rp = calculation(rq);      // 得到结构化数据：result + errnum
        logMessage(DEBUG, "result calculated: %d, errnum: %d", rp.result, rp.errnum);;
        // 4. 计算完成，将结构化数据序列化
        std::string result = rp.serialize();
        logMessage(DEBUG, "json序列化: %s", result.c_str());
        // 5. 将序列化数据打包，添加协议报头和分隔符，再发送会客户端
        encode(result);
        logMessage(DEBUG, "package encoded to: %s", result.c_str());
        Send(result, sock);
        logMessage(NORMAL, "result obtained and sent back done");
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        server_usage(argv[0]);
        exit(1);
    }
    signal(SIGPIPE, SIG_IGN);           // 服务器编写时必须具有较强的健壮性，子进程的退出与否不能影响服务器，一般都要忽略SIGPIPE，防止非法写入（send）
    TcpServer tp(atoi(argv[1]));        // 传入绑定的服务器端口号，自动完成服务器进程守护脱离，套接字创建，绑定和监听
    tp.exe_registration(calculator);    // 将需要服务器执行的回调方法传入登记
    tp.start();         // 开始执行对应服务（accept客户端请求，传入方法执行）
    return 0;
}