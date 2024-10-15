#ifndef __LOG_HPP
#define __LOG_HPP
#pragma once

#include <iostream>
#include <cstdio>
#include <string>
#include <ctime>
#include <stdarg.h>

#define DEBUG 0
#define NORMAL 1
#define WARNING 2
#define ERROR 3
#define FATAL 4
#define SIZE 1024

const char* levelMessage[] = {
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
    // standard
    char stdbuffer[SIZE];
    std::snprintf(stdbuffer, sizeof stdbuffer, "[%s] [%ld] ", levelMessage[level], t);
    // customized
    char cstbuffer[SIZE];
    va_list args;
    va_start(args, format);
    std::vsnprintf(cstbuffer, sizeof cstbuffer, format, args);
    va_end(args);
    printf("%s%s\n", stdbuffer, cstbuffer);
}

#endif