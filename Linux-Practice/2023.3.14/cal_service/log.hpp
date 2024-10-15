#ifndef __LOG_HPP
#define __LOG_HPP
#pragma once
#include <iostream>
#include <string>
#include <stdarg.h>
#include <ctime>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define DEBUG 0
#define NORMAL 1
#define WARNING 2
#define ERROR 3
#define FATAL 4
#define SIZE 512
#define LOGPATH "./cal.log"

static const char* levelMap[] = {
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

    //printf("%s %s\n", stdbuf, cstbuf);        // 前台服务器打印调试或请求信息

    FILE* fp = fopen(LOGPATH, "a");          // 将请求或各种调试信息存入日志文档中
    fprintf(fp, "%s %s\n", stdbuf, cstbuf);
    fclose(fp);

    // int fd = open(LOGPATH, O_CREAT | O_WRONLY | O_APPEND, 0666);        // 另一种写入方式，需要三者配合输入
    // assert(fd != -1);
    // write(fd, stdbuf, strlen(stdbuf));
    // write(fd, cstbuf, strlen(cstbuf));
    // close(fd);
}

#endif