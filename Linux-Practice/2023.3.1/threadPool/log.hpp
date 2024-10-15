#pragma once
#include "thread.hpp"

// 日志有日志级别，完整的日志需要有：日至等级，时间，内容，支持用户自定义
#define DEBUG 0
#define NORMAL 1
#define WARNING 2
#define ERROR 3         // 错误但不影响执行
#define FATAL 4         // 崩溃

const char* logLevel[] = {
    "DEBUG",
    "NORMAL",
    "WARNING",
    "ERROR",
    "FATAL"
};

const char* filepath = "./logtext.log";

void logMessage(int level, const char* format, ...) {
#ifdef DEBUG
    if(level == DEBUG) return;
#endif
    // 1. 标准日志
    time_t t = time(nullptr);
    char stdbuffer[1024];
    snprintf(stdbuffer, sizeof stdbuffer, "[%s] | [%ld]", logLevel[level], t);
    // 2. 自定义内容块
    char cstbuffer[1024];
    va_list args;       // 用户获取可变参数列表的指针和格式化输出函数
    va_start(args, format);
    vsnprintf(cstbuffer, sizeof cstbuffer, format, args);
    va_end(args);
    printf("%s | %s", stdbuffer, cstbuffer);
    FILE* fp = fopen(filepath, "a");
    fprintf(fp, "%s%s\n", stdbuffer, cstbuffer);
    fclose(fp);
}