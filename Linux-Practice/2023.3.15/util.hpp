#ifndef __UTIL_HPP
#define __UTIL_HPP
#include <iostream>
#include <vector>
#include <string>
#define SPACE " "
#define SPACE_LEN 1
#define SEP "\r\n"
#define SEP_LEN 2

class Util{
public:
    // 切割请求报文的每一行
    std::vector<std::string> line_seperate(std::string& request) {
        std::vector<std::string> v;
        std::string line;
        while(true) {
            size_t pos = request.find(SEP);
            line = request.substr(0, pos);
            if(line.empty()) break;
            logMessage(DEBUG, "get line: %s", line.c_str());
            v.push_back(line);
            request.erase(0, pos + SEP_LEN);
        }
        return v;
    }

    // 切割报文每一行的每一个字段
    std::vector<std::string> words_seperate (std::string& line) {
        std::vector<std::string> v;
        std::string word;
        while(true) {
            size_t pos = line.find(SPACE);
            if(pos == std::string::npos) {
                if(pos = line.find(SEP)) {
                    word = line.substr(0, pos);
                    v.push_back(word);
                }
                break;
            }
            word = line.substr(0, pos);
            v.push_back(word);
            word = line.erase(0, pos + SPACE_LEN);
        }
        for(auto& it: v) {
            logMessage(DEBUG, "get word: %s", it.c_str());
        }
        return v;
    }
};

#endif