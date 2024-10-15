#include "tcp_server.hpp"

static void server_usage(const char* proc) {
    std::cout << "usage: " << proc << " port" << std::endl;
}

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
            if(rq.m_y == 0) rp.errnum = 1;
            else rp.result = rq.m_x / rq.m_y;
        }
            break;
        case '%': {
            if(rq.m_y == 0) rp.errnum = 2;
            else rp.result = rq.m_x % rq.m_y;
        }
            break;
        default: rp.errnum = 3;
            break;
    }
    return rp;
}

void calculator(int sock) {
    while(true) {
        std::string str = Recv(sock);
        logMessage(NORMAL, "dataset obtained and ready to handle");
        Request rq;
        rq.deserialize(str);
        Response rp = calculation(rq);
        logMessage(DEBUG, "result calculated: %d, errnum: %d", rp.result, rp.errnum);;
        std::string result = rp.serialize();
        Send(result, sock);
        logMessage(NORMAL, "result obtained and sent back done");
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        server_usage(argv[0]);
        exit(1);
    }
    TcpServer tp(atoi(argv[1]));
    tp.exe_registration(calculator);
    tp.start();
    return 0;
}