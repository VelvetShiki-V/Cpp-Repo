#ifndef __TASK_HPP
#define __TASK_HPP
#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "TCPServer.hpp"
#include "protocol.hpp"
using std::string;
using std::vector;
#define SEPT ' '
#define SEPT_LEN 1

// 服务器数据业务处理——反转单词，去除冗余空格
void sentence_reverse(string& s, reactor::SockBlock* sb) {
    // 0. 将已经解包出的请求报文数据反序列化
    Request rq;
    // logMessage(DEBUG, "开始对接收到的序列化数据: %s进行反序列化", s.c_str());
    rq.deserialize(s);
    // logMessage(DEBUG, "反序列化完成，得到有效数据载荷: %s", s.c_str());
    // 1. 业务处理——逆序句子
    string rvs_str;
    int right = s.size() - 1;
    while(right >= 0) {     // 思路：去除句子首尾冗余空格，right从右到左遍历
        while(right >= 0 && s[right] == SEPT) right--;      // right找字母，left找空格
        if(right == -1) break;          // this is a sample sentence
        int left = right;
        while(left >= 0 && s[left] != SEPT) left--;
        rvs_str.append(s, left + SEPT_LEN, right - left);
        rvs_str += SEPT;
        right = left;
    }
    rvs_str.pop_back();     // 将每次加上的后缀空格，最后一次的冗余空格去除
    // logMessage(DEBUG, "单词反转业务处理完成，得到数据: %s", rvs_str.c_str());
    // 2. 序列化构建响应报文，添加到sock输出缓冲区中
    Response rp;
    rp.serialize(rvs_str);
    // logMessage(DEBUG, "响应数据序列化完成，序列化数据: %s", rvs_str.c_str());
    // 3. 将处理结果添加协议首尾
    encode(rvs_str);        // 放在服务器内部执行更好，完成数据业务处理和协议制定的解耦
    sb->out_buffer += rvs_str;
    // logMessage(DEBUG, "协议encode成功，得到响应报文: %s", sb->out_buffer.c_str());
    // 4. 响应报文由tcpServer代为发送
    sb->write_cb(sb);       // 无需使用回值指针，直接调用写IO方法
    // 或使用回值指针打开读写权限的方式，但要额外定制enable_read_write类来完成
}

#endif