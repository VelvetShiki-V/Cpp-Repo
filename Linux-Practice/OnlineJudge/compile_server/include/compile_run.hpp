#ifndef __COMPILE_RUN_HPP
#define __COMPILE_RUN_HPP
#pragma once

#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include <unistd.h>
#include "compiler.hpp"
#include "runner.hpp"
#include "../../comm/log.hpp"
#include "../../comm/util.hpp"
#define SUCCESS 0
#define NULL_FILE -1
#define SVR_ERROR -2
#define COMPILE_ERROR -3
#define RUN_ERROR -4

namespace svr_compile_run {
    using namespace svr_compiler;
    using namespace svr_runner;
    using namespace svr_util;
    using namespace svr_log;
    class compile_run {
    public:
        // 进程信号捕捉函数
        static std::string catch_signal(const int &run_status) {
            std::string run_desc;
            switch(run_status) {
                case SIGSEGV: {
                    run_desc = "segmentation fault";
                    break;
                }
                case SIGFPE: {
                    run_desc = "process result obtained is inconsistent of the accuracy regulated";
                    break;
                }
                case SIGXCPU: {
                    run_desc = "process running exceeds time limit";
                    break;
                }
                case SIGABRT: {
                    run_desc = "process overloads, aborted";
                    break;
                }
                default: {
                    run_desc = "unknown running error";
                    break;
                }
            }
            return run_desc;
        }
        // 服务器对用户代码的编译运行情况
        static std::string status_describe(const int &status, const int &run_status, const std::string &file_name) {
            std::string reason;
            switch(status) {
                case SUCCESS: {                  // 运行函数返回0，运行成功
                    reason = "user code compiling and running successfully";
                    break;
                }
                case NULL_FILE: {                // 空文件，系统无法读取
                    reason = "user submitted nothing";
                    break;
                }
                case SVR_ERROR: {                // 将代码写入源文件失败，或用户代码唯一文件名获取失败，系统错误
                    reason = "server error";
                    break;
                }
                case COMPILE_ERROR: {            // 用户代码编译错误
                    std::string err_message;
                    file_util::read_from_file(path_util::err(file_name), &err_message);
                    reason = "user code compiling failed:\n" + err_message;
                    break;
                }
                case RUN_ERROR: {               // 用户exe文件运行错误
                    reason = "user code running failed: " + catch_signal(run_status);
                    break;
                }
                default: {
                    reason = "unknown error, status: " + std::to_string(status);
                    break;
                }
            }
            return reason;
        }
        
        // 中间临时文件清除
        static void tmp_file_cleaner(const std::string file_name, bool keep_src = false) {
            if(!keep_src) unlink(path_util::src(file_name).c_str());
            unlink(path_util::exe(file_name).c_str());
            unlink(path_util::err(file_name).c_str());
            unlink(path_util::Stdin(file_name).c_str());
            unlink(path_util::Stdout(file_name).c_str());
            unlink(path_util::Stderr(file_name).c_str());
        }

        // 编译运行服务
        static void run(const std::string& in, std::string* out) {
            // 1. 对请求报文进行反序列化
            Json::Reader reader;
            Json::Value rvalue;
            reader.parse(in, rvalue);       // 将序列化Json串数据转化为键值对数据
            // 2. 数据解析到结构化数据中
            std::string input = rvalue["input"].asString();
            std::string code = rvalue["code"].asString();
            int cpu_limit = rvalue["cpu"].asInt();
            int memory_limit = rvalue["memory"].asInt();
            // 3. 差错处理
            int status = 0;         // 定义状态码和状态说明
            int run_status = 0;
            std::string reason;
            std::string code_file_name;  // 获取到的代码唯一文件名
            if(code == "") {
                status = NULL_FILE; 
                goto END;
            }
            // 4. 将代码写入文件内，对源文件编译运行
            code_file_name = file_util::get_unique_file_name();
            if(code_file_name == "") {
                status = SVR_ERROR; 
                goto END;
            }
            if(!file_util::write_to_file(path_util::src(code_file_name), code)) {
                status = SVR_ERROR;   
                goto END;
            }
            if(!compiler::compile(code_file_name)) {
                status = COMPILE_ERROR;
                goto END;
            }
            if(run_status = runner::run(code_file_name, cpu_limit, memory_limit)) {
                if(run_status < 0) status = SVR_ERROR;
                else status = RUN_ERROR;
                goto END;
            }
            END:
            {
                // 将编译运行结果写入json键值对数据中
                Json::Value wvalue;
                wvalue["status"] = status;
                wvalue["reason"] = status_describe(status, run_status, code_file_name);
                LOG(INFO) << wvalue["reason"] << std::endl;
                // 若编译运行成功，需要额外将运行结果存起来
                if(status == SUCCESS) {
                    std::string stdout_content;
                    if(!file_util::read_from_file(path_util::Stdout(code_file_name), &stdout_content)) {
                        LOG(FATAL) << "user code compiling and running success, while response file output failed" << std::endl;
                    }
                    wvalue["stdout"] = stdout_content;
                    std::string stderr_content;
                    if(!file_util::read_from_file(path_util::Stderr(code_file_name), &stderr_content)) {
                        LOG(FATAL) << "user code compiling and running success, while response file output failed" << std::endl;
                    }
                    wvalue["stderr"] = stderr_content;
                }
                // json键值对数据序列化，构建json串
                Json::StyledWriter writer;
                *out = writer.write(wvalue);
                // 清除中间临时文件
                // tmp_file_cleaner(code_file_name, true);     // 条件为真保留源文件
            }
        }
    };
}

#endif      // __COMPILE_RUN_HPP