#ifndef __LOG_HPP
#define __LOG_HPP
#pragma once

#include <iostream>
#include <cstdio>
#include <stdarg.h>
#include <string>
#include <ctime>
#define DEBUG_NOTSHOW 1
#define MESSAGE_NOTSHOW 2
#define LOG_PATH "./memory_log.txt"

#define DEBUG 0
#define NORMAL 1
#define WARNING 2
#define ERRO 3
#define FATAL 4
#define SIZEE 128

// 日志等级
const char* levelMap[] = {
    "DEBUG"
    ,"NORMAL"
    ,"WARNING"
    ,"ERROR"
    ,"FATAL"
};

void logMessage(int level, const char* format, ...) {
#ifdef MESSAGE_NOTSHOW      // 用于调试时打印在屏幕上的日志信息，便于debug
    return;
#endif
#ifdef DEBUG_NOTSHOW
    if (levelMap[level] == "DEBUG") return;
#endif
    time_t t = time(nullptr);
    // std
    char stdbuf[SIZEE];
    snprintf(stdbuf, sizeof stdbuf, "[%s] | [%lld] | ", levelMap[level], t);
    // cst
    char cstbuf[SIZEE];
    va_list args;
    va_start(args, format);
    vsnprintf(cstbuf, sizeof cstbuf, format, args);
    va_end(args);
    // printf("%s%s\n", stdbuf, cstbuf);       // 打印在屏幕上便于调试
    FILE* fp = fopen(LOG_PATH, "a");
    fprintf(fp, "%s%s\n", stdbuf, cstbuf);    // 日志信息存储到文件中
    fclose(fp);
}

#endif