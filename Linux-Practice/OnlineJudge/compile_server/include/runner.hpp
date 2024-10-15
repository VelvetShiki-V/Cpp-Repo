#ifndef __RUNNER_HPP
#define __RUNNER_HPP
#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include "../../comm/log.hpp"
#include "../../comm/util.hpp"

namespace svr_runner{
    using namespace svr_util;
    using namespace svr_log;
    class runner{
    public:
        static int run(const std::string file_name, int cpu_time, int mem_spc) {
            // 1. 定义好待运行的exe路径，并根据可执行文件定义好相关临时文件路径
            const std::string exe_path = path_util::exe(file_name);
            const std::string stdin_path = path_util::Stdin(file_name);
            const std::string stdout_path = path_util::Stdout(file_name);
            const std::string stderr_path = path_util::Stderr(file_name);
            // 2. 父进程打开对应临时文件
            umask(0);
            int in_fd = open(stdin_path.c_str(), O_CREAT | O_RDONLY, 0644);
            int out_fd = open(stdout_path.c_str(), O_CREAT | O_WRONLY, 0644);
            int err_fd = open(stderr_path.c_str(), O_CREAT | O_WRONLY, 0644);
            if(in_fd < 0 || out_fd < 0 || err_fd < 0) {
                LOG(FATAL) << "standard file of solution exe open failed: " << exe_path << std::endl;
                return -1;      // 文件打开失败
            }
            // 3. 创建子进程，重定向，进程替换并运行
            pid_t id = fork();
            if(id < 0) {
                LOG(FATAL) << "solution exe fork failed: " << exe_path << std::endl;
                close(in_fd);
                close(out_fd);
                close(err_fd);
                return -2;      // 子进程创建失败
            }
            else if(id == 0) {
                // child proc：输入输出错误流重定向至对应文件中，并限制子进程资源使用上限
                dup2(in_fd, 0);
                dup2(out_fd, 1);
                dup2(err_fd, 2);
                if(!set_rsc_constraint(cpu_time, mem_spc)) return -3;       // 时间空间上限设置失败
                if(execl(exe_path.c_str(), exe_path.c_str(), nullptr) < 0) {
                    close(in_fd);
                    close(out_fd);
                    close(err_fd);
                    return -4;      // 子进程替换失败
                }
            }
            // parent proc
            close(in_fd);
            close(out_fd);
            close(err_fd);
            int status = 0;
            if(waitpid(id, &status, 0) < 0) {
                LOG(FATAL) << "solution exe wait failed: " << __func__ << std::endl;
                return -5;          // 子进程等待失败
            }
            LOG(INFO) << "solution exe running success, signal obtained: " << (status & 0x7F) << std::endl;
            return status & 0x7F;       // 返回子进程运行退出时的信号
        }
    private:
        static bool set_rsc_constraint(int cpu_time, int mem_spc) {
            // 设置CPU资源时间使用上限
            struct rlimit r_time;
            r_time.rlim_max = RLIM_INFINITY;
            r_time.rlim_cur = cpu_time;
            if(setrlimit(RLIMIT_CPU, &r_time) < 0) return false;
            // 设置内存资源空间使用上限
            struct rlimit r_space;
            r_space.rlim_max = RLIM_INFINITY;
            r_space.rlim_cur = mem_spc * 1024;
            if(setrlimit(RLIMIT_AS, &r_space) < 0) return false;
            return true;
        }
    };
}

#endif // __RUNNER_HPP