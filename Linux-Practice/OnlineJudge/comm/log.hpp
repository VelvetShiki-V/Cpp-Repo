#ifndef __LOG_HPP
#define __LOG_HPP
#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "util.hpp"
#define LOG(level) svr_log::log(#level, __FILE__, __func__, __LINE__)

namespace svr_log{
    enum {
        INFO,
        DEBUG,
        WARNING,
        ERROR,
        FATAL
    };

    inline std::ostream &log(const std::string &level, const std::string &filename, const std::string &funcname, int line) {
        std::string logMessage;
        // 日志等级
        logMessage = '[' + level + ']';
        // 错误文件信息
        logMessage += " | [" + filename + ']';
        // 错误函数
        logMessage += " | [function: " + funcname + ']';
        // 错误行
        logMessage += " | [line: " + std::to_string(line) + ']';
        // 时间戳
        logMessage += " | [" + std::to_string(time(nullptr)) + "]";
        std::cout << logMessage << std::endl;
        return std::cout;
    }
}


#endif // __LOG_HPP