#ifndef __LOG_HPP
#define __LOG_HPP
#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <cstdarg>
#define DEBUG 0
#define NORMAL 1
#define WARNING 2
#define ERROR 3
#define FATAL 4
#define SIZE 512
#define LOG_PATH "./request.log"
#define NON_DEBUG

static const char* levelMap[] = {
    "DEBUG"
    ,"NORMAL"
    ,"WARNING"
    ,"ERROR"
    ,"FATAL"
};

void logMessage(int level, const char* format, ...) {
#ifdef NON_DEBUG
    if(levelMap[level] == "DEBUG") return;
#endif
    // std
    time_t t = time(nullptr);
    char stdbuf[SIZE];
    snprintf(stdbuf, sizeof stdbuf, "[%s] | [%ld]", levelMap[level], t);
    // cst
    char cstbuf[SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(cstbuf, sizeof cstbuf, format, args);
    va_end(args);

    printf("%s %s\n", stdbuf, cstbuf);      // 标准输出
}

#endif