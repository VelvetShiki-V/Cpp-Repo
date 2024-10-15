#ifndef __LOG_HPP
#define __LOG_HPP
#pragma once
#include <iostream>
#include <string>
#include <stdarg.h>
#include <ctime>

#define DEBUG 0
#define NORMAL 1
#define WARNING 2
#define ERROR 3
#define FATAL 4
#define SIZE 512

const char* levelMap[] = {
    "DEBUG"
    ,"NORMAL"
    ,"WARNING"
    ,"ERROR"
    ,"FATAL"
};

void logMessage(int level, const char* format, ...) {
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
    printf("%s %s\n", stdbuf, cstbuf);
}

#endif