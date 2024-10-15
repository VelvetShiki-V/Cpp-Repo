#ifndef __COMPILER_HPP
#define __COMPILER_HPP
#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "runner.hpp"
#include "../../comm/log.hpp"
#include "../../comm/util.hpp"

namespace svr_compiler {
    using namespace svr_log;
    using namespace svr_util;
    using namespace svr_runner;
    class compiler{
    public:
        static bool compile(const std::string &filename) {
            pid_t id = fork();
            if(id < 0) {
                LOG(FATAL) << "file compiling fork failed" << std::endl;
                return false;
            }
            else if(id == 0) {
                // child proc
                // 1. 将标准错误流重定向到err文件中
                umask(0);
                int fd = open(path_util::err(filename).c_str(), O_CREAT | O_WRONLY, 0644);      // wrr
                if(fd < 0) {
                    LOG(FATAL) << " compiling message file open failed" << std::endl;
                    return false;
                }
                else {
                    // 错误文件创建/打开成功，重定向
                    if(dup2(fd, 2) < 0) {
                        LOG(FATAL) << "compiling message redirect into file failed" << std::endl;
                        return false;
                    }
                }
                // 2. 子进程替换为g++编译器程序
                if(execlp("g++", "g++", "-o", path_util::exe(filename).c_str(), \
                path_util::src(filename).c_str(), "-std=c++11", nullptr) < 0) {
                    LOG(FATAL) << filename << " compiling process execlp failed" << std::endl;
                    exit(1);
                }
            }
            else {
                // parent proc
                // 等待子进程，验证文件是否被正确创建
                if(waitpid(id, nullptr, 0) < 0) {
                    LOG(FATAL) << "compiling child process pid: " << id << " wait failed" << std::endl;
                    return false;
                }
                else {
                    if(file_util::IsFileExisted(path_util::exe(filename)) && \
                    file_util::IsFileExisted(path_util::err(filename))) {
                        LOG(INFO) << "compile success, belonging exe & err is currently generated" << std::endl;
                        return true;
                    }
                    else LOG(ERROR) << "compile failed, solution exe generate failed" << std::endl;
                }
            }
            return false;
        }
public:
        void run(const std::string &filename, const int &cpu_time, const int &mem_spc) {
            if(this->compile(filename)) runner::run(filename, cpu_time, mem_spc);
        }
    };
}

#endif  // __COMPILER_HPP