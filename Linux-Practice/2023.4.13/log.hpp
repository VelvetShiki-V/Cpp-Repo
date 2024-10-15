#ifndef __LOG_HPP
#define __LOG_HPP
#pragma once
#include <iostream>
#include <ctime>
#include <cstring>
#include <stdarg.h>

#define DEBUG 0
#define NORMAL 1
#define WARNING 2
#define ERROR 3
#define FATAL 4
#define MSG_SIZE 512

const char* levelMap[] = {
    "DEBUG"
    ,"NORMAL"
    ,"WARNING"
    ,"ERROR"
    ,"FATAL"
};

void logMessage(int level, const char* format, ...) {
#ifdef DEBUG_NOTSHOW
    if(level == DEBUG) return;
#endif
    time_t t = time(nullptr);
    // std
    char stdbuf[MSG_SIZE];
    snprintf(stdbuf, sizeof stdbuf - 1, "[%s] | [%lld] ", levelMap[level], t);
    // cst
    char cstbuf[MSG_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(cstbuf, sizeof cstbuf - 1, format, args);
    va_end(args);
    // output
    printf("%s%s\n", stdbuf, cstbuf);
}
#endif