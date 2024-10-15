#ifndef __PROTOCOL_HPP
#define __PROTOCOL_HPP
#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <string>
#include <jsoncpp/json/json.h>      // 完整的json头文件
#include "log.hpp"
#define SIZEE 1024
#define SPACE " "
#define SPACE_LEN 1
#define SEP "\r\n"
#define SEP_LEN strlen(SEP)
// #define CST_APPROCH 0

// 服务器与客户端都需要共享的计算结果状态信息
static const char* err_info[] = {
    "结果正确"
    ,"除0错误"
    ,"运算符解析失败"
};

// 请求推送的序列化与反序列化类
class Request{
public:
    Request(){}
    ~Request(){}
    // 传入结构化数据进行序列化，以string返回
    std::string serialize(int x, int y, char op) {
#ifdef CST_APPROCH
        // 自定义协议方案
        std::string output;
        output += std::to_string(x);      // format: x + y
        output += SPACE;
        output += op;
        output += SPACE;
        output += std::to_string(y);
        logMessage(DEBUG, "序列化为: %s", output.c_str());
        return output;
#else
        // json方案
        Json::Value key;
        key["x"] = x;
        key["y"] = y;
        key["op"] = op;
        Json::FastWriter writer;
        return writer.write(key);
#endif
    }
    bool deserialize(const std::string& str) {
#ifdef CST_APPROCH
        // 按照x + y的格式反序列化
        size_t left = str.find(SPACE);      // find找左右分隔符，再以分隔符子串substr提取结构化成员属性x, y, op
        if(left == std::string::npos) return false;
        size_t right = str.rfind(SPACE);
        if(right == std::string::npos) return false;
        m_x = atoi(str.substr(0, left).c_str());
        m_y = atoi(str.substr(right + SPACE_LEN, std::string::npos).c_str());
        if(left + SPACE_LEN > str.size()) return false;
        else m_op = str[left + SPACE_LEN];
        logMessage(DEBUG, "反序列化为: x: %d   y: %d  op: %c", m_x, m_y, m_op);
        return true;
#else
        // json 方案
        Json::Value key;
        Json::Reader reader;
        reader.parse(str, key);
        m_x = key["x"].asInt();
        m_y = key["y"].asInt();
        m_op = key["op"].asInt();
        return true;
#endif
    } 
public:
    int m_x;
    int m_y;
    char m_op;
};

// 响应类的序列化与反序列化
class Response{
public:
    Response(){ 
        result = 0;
        errnum = 0;
    }
    ~Response(){}
    std::string serialize() {
#ifdef CST_APPROCH
        // 按照result errnum的格式序列化
        std::string output;
        output += std::to_string(result);
        output += SPACE;
        output += std::to_string(errnum);
        return output;
#else
        // json方案
        Json::Value key;
        key["result"] = result;
        key["errnum"] = errnum;
        Json::FastWriter writer;
        return writer.write(key);
#endif
    }
    bool deserialize(std::string str) {    // result errnum
#ifdef CST_APPROCH
        size_t sep = str.find(SPACE);
        if(sep == std::string::npos) return false;
        result = atoi(str.substr(0, sep).c_str());
        errnum = atoi(str.substr(sep + SPACE_LEN, std::string::npos).c_str());
        return true;
#else
        // json方案
        Json::Value key;
        Json::Reader reader;
        reader.parse(str, key);
        result = key["result"].asInt();
        errnum = key["errnum"].asInt();
        return true;
#endif
    }
public:
    int result;
    int errnum;
};

void Send(const std::string& str, int sock) {
    // sockaddr_in toServer;        // sendto接口使用，send亦能使用（sock已经完成了前置工作）
    ssize_t s = send(sock ,str.c_str(), str.size(), 0);
    if(s < 0) {     // 服务器发送给客户端，但对端已经关闭，此时sock文件描述符已解绑，将会产生SIGPIPE信号给服务器，使其关闭（隐患）
        std::cout << "data send fail" << std::endl;
        exit(1);
    }
}

const std::string Recv(int sock) {
    sockaddr_in fromClient;
    socklen_t len = sizeof fromClient;
    char recbuf[SIZEE];
    ssize_t r = recvfrom(sock, recbuf, sizeof recbuf, 0, (sockaddr*)&fromClient, &len);     // 与recv通用
    if(r < 0) {
        logMessage(FATAL, "%d:%s", errno, strerror(errno));
    }
    else if(r == 0) {
        logMessage(ERROR, "对端关闭, 接收数据量为0");       // 如果客户端关闭，则服务器接收不到数据
    }
    recbuf[r] = 0;
    return recbuf;
}

// TCP字节流传输模式，需要对数据进行完整性验证
// 添加协议首尾，以区分每个完整的数据，format: [length\r\nm_x m_op m_y\r\n][...]
void encode(std::string& package){
    std::string package_length = std::to_string(package.size());
    package.insert(0, SEP);
    package.insert(0, package_length);
    package += SEP;
}

// 服务器或客户端在接收到数据后，先进行完整性验证，返回空串代表数据不完整，将循环解码以获取完整数据，并以string返回
std::string decode(std::string str) {      // format: [length\r\nm_x m_op m_y\r\n][...]
    size_t pos = str.find(SEP);
    if(pos == std::string::npos) return "";                 // 寻找分隔符SEP: \r\n
    size_t str_length = atoi(str.substr(0, pos).c_str());   // 提取length中代表的数据长度
    size_t surplus = str.size() - pos - SEP_LEN * 2;        // 数据字节流可能不止一个，如果排除分隔符和length的数据载荷长度比length短，说明数据不完整，返回空串
    if(surplus >= str_length) {
        str.erase(0, pos + SEP_LEN);                        // 为了提取有效数据载荷，需要抹除协议首尾
        std::string output = str.substr(0, str_length);     // 使用substr提取
        str.erase(0, str_length + SEP_LEN);
        return output;
    }
    return "";
}

#endif