#ifndef __HTTP_SERVER_HPP
#define __HTTP_SERVER_HPP
#include <iostream>
#include <string>
#include <functional>
#include <signal.h>
#include <unistd.h>
#include "sock.hpp"
#include "log.hpp"
#include "util.hpp"
#include <vector>
#include <fstream>
#define ROOT_PATH "./wwwroot"
#define HOME_PAGE "/index.html"
#define EMPTY_PATH "/"
#define DEFAULT_PATH "/favicon.ico"

class Http_Server{
public:
    using func_t = std::function<void(int)>;

    Http_Server(const uint16_t& port, func_t callback)
    :execution(callback)
    {
        listen_sock = m_sock.socket_create();
        m_sock.socket_bind(listen_sock, port);
        m_sock.socket_listen(listen_sock);
        logMessage(NORMAL, "Http server init done");
    }

    void start() {
        logMessage(NORMAL, "ready to serve");
        signal(SIGCHLD, SIG_IGN);
        while(true) {
            std::string cli_ip;
            uint16_t cli_port;
            int service_sock = m_sock.socket_accept(listen_sock, cli_ip, cli_port);
            if(service_sock < 0) continue;
            // 创建子进程接收服务
            pid_t id = fork();
            if(id < 0) {
                logMessage(FATAL, "fork error, %d:%s", errno, strerror(errno));
                exit(4);
            }
            if(id == 0) {       // 子进程
                close(listen_sock);
                logMessage(NORMAL, "pid: %d is serving...", getpid());
                execution(service_sock);
                logMessage(NORMAL, "service finished");
                close(service_sock);
                exit(5);
            }
            close(service_sock);
        }
    }

    ~Http_Server() {
        if(listen_sock > 0) {
            close(listen_sock);
        }
    }
private:
    int listen_sock;
    Socket m_sock;
    func_t execution;
};

// http响应方法
void http_response(const int& sock) {
    // 1. 获取web请求报文
    logMessage(NORMAL, "service conducting, sock: %d", sock);
    std::string str = Recv(sock);
    std::vector<std::string> v1;
    std::vector<std::string> v2;
    logMessage(DEBUG, "######################################################");
    // 2. 提取报文的每一行（请求行 + 请求报头 + 正文）
    Util msg;
    v1 = msg.line_seperate(str);
    logMessage(DEBUG, "Headline: %s", v1[0].c_str());

    // 3. 提取请求行中URL的资源路径和目标文件名
    v2 = msg.words_seperate(v1[0]);
    logMessage(DEBUG, "words count: %d", v2.size());
    logMessage(DEBUG, "rsc_path: %s", v2[1].c_str());
    if(v2[1] == EMPTY_PATH || v2[1] == DEFAULT_PATH) v2[1] = HOME_PAGE;
    std::string target_path = ROOT_PATH + v2[1];
    logMessage(NORMAL, "target_path obtained: %s", target_path.c_str());

    // 4. 按行读取目标文件中的资源
    std::string content;
    std::ifstream in(target_path);
    if(in.is_open()) {
        logMessage(DEBUG, "target file open success, path: %s", target_path.c_str());
        std::string line;  
        while(getline(in, line)) {
            content += line;
            logMessage(DEBUG, "reading target file, each line: %s", line.c_str());
        }
        in.close();
    }

    // 5. 检测资源获取状态，填充状态行
    std::string http_response;
    if(content.empty()) {
        logMessage(ERROR, "请求资源失败");
        // http_response = "HTTP/1.1 404 NotFound\r\n";
        http_response = "HTTP/1.1 302 Found\r\n";           // 临时移动
        // http_response += "Location: http://baidu.com\r\n";      // 如果目标资源未获取到，跳转到指定站点
        http_response = "HTTP/1.1 301 Moved Permanently\r\n";           // 永久移动
        http_response += "Location: http://119.3.179.90:8080/status/ErrorPage.html\r\n";
    }
    else {
        logMessage(NORMAL, "资源已获取");

        // 5.1 响应状态行
        http_response = "HTTP/1.1 200 OK\r\n";

        // 5.2 响应报头
        http_response += "content-length: " + std::to_string(content.length()) + "\r\n";     // 有效载荷长度
        http_response += "content-type: text/html\r\n";    // 传输类型：纯文本数据的html类型，如果写为text/plain，浏览器将不再对html代码做解释
        http_response += "Set-Cookie: this is a cookie\r\n";
    }
    // 6. 填充空行和响应报文正文
    http_response += SEP;
    http_response += content;
    logMessage(DEBUG, "http_response verify:\n%s", http_response.c_str());

    // 7. 向请求方响应反馈
    ssize_t s = send(sock, http_response.c_str(), http_response.size(), 0);
    if(s < 0) {
        logMessage(FATAL, "http_response sent back fail, %d:%s", errno, strerror(errno));
        exit(3);
    }
    logMessage(NORMAL, "http_response sent back success");
}

#endif