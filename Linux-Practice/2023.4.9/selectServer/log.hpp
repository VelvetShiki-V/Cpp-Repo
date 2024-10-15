#ifndef __LOG_HPP
#define __LOG_HPP
#include <iostream>
#include <ctime>
#include <string>
#include <cstring>
#include <stdarg.h>

#define MSG_SIZE 512
#define DEBUG 0
#define NORMAL 1
#define WARNING 2
#define ERROR 3
#define FATAL 4
// #define DEBUG_NOTSHOW 1
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
    printf("%s%s\n", stdbuf, cstbuf);
}

#endif