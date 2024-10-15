#ifndef __PROTOCOL_HPP
#define __PROTOCOL_HPP
#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "log.hpp"
using std::string;
using std::vector;
#define ENCODE_SEP "$"
#define ENCODE_SEPLEN strlen(ENCODE_SEP)

// 1. 先对待发送数据序列化反序列化（对字符串不做处理）
class Request {
public:
    void serialize(string& input) {}
    void deserialize(string& input) {}
};

class Response {
public:
    void serialize(string& input) {}
    void deserialize(string& input) {}
};

// 2. 再对序列化数据添加/移除报文首尾协议字段
void decode(string& s, vector<string>& v) {
    // format:[length][$][abcde][$][...]
    while(true) {
        // 1. 寻找协议分隔符——粘包问题解决
        size_t sep_pos = s.find(ENCODE_SEP);
        if(sep_pos == string::npos) {
            // logMessage(ERROR, "decode failed-%d:%s", errno, strerror(errno));
            break;      // 若找不到分隔符，说明1. 数据不完整 2. 接收缓冲区为空
        }
        // 2. 计算报文长度是否合法——协议首字段为有效载荷长度，长度对应不上则报文不完整，不应处理
        // logMessage(DEBUG, "截取有效字段长度: %s, sep_pos在下标: %d", s.substr(0, sep_pos).c_str(), sep_pos);
        int cent_len = atoi(s.substr(0, sep_pos).c_str());
        int get_len = s.size() - 2 * ENCODE_SEPLEN - sep_pos;
        // logMessage(DEBUG, "报文长度: %d, 有效字段长度: %d, 实际字段接收长度: %d",s.size(), cent_len, get_len);
        if(get_len < cent_len) {
            logMessage(ERROR, "decoded message incomplete-%d:%s", errno, strerror(errno));
            break;
        }
        // 2. 长度合法，提取报文到vector中（因为可能同时存在多个报文，循环提取），并清除数据和协议首尾
        s.erase(0, sep_pos + ENCODE_SEPLEN);
        v.push_back(s.substr(0, get_len));
        s.erase(0, get_len + ENCODE_SEPLEN);
        // logMessage(DEBUG, "提取的报文: %s", v[0].c_str());
    }
}

// 将未序列化的报文添加协议首尾
bool encode(string& s) {
    // 添加协议：format:[length][$][abcde][$][...]
    if(s.empty()) return false;
    size_t size = s.size();
    s.insert(0, ENCODE_SEP);
    s.insert(0, std::to_string(size));
    s += ENCODE_SEP;
    return true;
}

#endif