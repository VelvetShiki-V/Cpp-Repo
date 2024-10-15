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
#include "log.hpp"
#define SIZEE 1024
#define SPACE " "
#define SPACE_LEN 1

class Request{
public:
    Request(){}
    ~Request(){}
    std::string serialize(int x, int y, char op) {
        std::string output;
        output += std::to_string(x);      // format: x + y
        output += SPACE;
        output += op;
        output += SPACE;
        output += std::to_string(y);
        logMessage(DEBUG, "序列化为: %s", output.c_str());
        return output;
    }
    bool deserialize(const std::string& str) {
        // 按照x + y的格式反序列化
        size_t left = str.find(SPACE);
        if(left == std::string::npos) return false;
        size_t right = str.rfind(SPACE);
        if(right == std::string::npos) return false;
        m_x = atoi(str.substr(0, left).c_str());
        m_y = atoi(str.substr(right + SPACE_LEN, std::string::npos).c_str());
        if(left + SPACE_LEN > str.size()) return false;
        else m_op = str[left + SPACE_LEN];
        logMessage(DEBUG, "反序列化为: x: %d   y: %d  op: %c", m_x, m_y, m_op);
        return true;
    } 
public:
    int m_x;
    int m_y;
    char m_op;
};

class Response{
public:
    Response(){ 
        result = 0;
        errnum = 0;
    }
    ~Response(){}
    std::string serialize() {
        // 按照result errnum的格式序列化
        std::string output;
        output += std::to_string(result);
        output += SPACE;
        output += std::to_string(errnum);
        return output;
    }
    bool deserialize(std::string str) {    // result errnum
        size_t sep = str.find(SPACE);
        if(sep == std::string::npos) return false;
        result = atoi(str.substr(0, sep).c_str());
        errnum = atoi(str.substr(sep + SPACE_LEN, std::string::npos).c_str());
        return true;
    }
public:
    int result;
    int errnum;
};

void Send(const std::string& str, int sock) {
    sockaddr_in toServer;
    ssize_t s = send(sock ,str.c_str(), str.size(), 0);
    if(s < 0) {
        std::cout << "data send fail" << std::endl;
        exit(1);
    }
}

const std::string Recv(int sock) {
    sockaddr_in fromClient;
    socklen_t len = sizeof fromClient;
    char recbuf[SIZEE];
    ssize_t r = recvfrom(sock, recbuf, sizeof recbuf, 0, (sockaddr*)&fromClient, &len);
    if(r < 0) {
        logMessage(FATAL, "%d:%s", errno, strerror(errno));
    }
    recbuf[r] = 0;
    std::string s = recbuf;
    return s;
} 

#endif