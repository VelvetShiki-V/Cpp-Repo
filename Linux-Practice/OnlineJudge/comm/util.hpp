#ifndef __UTIL_HPP
#define __UTIL_HPP
#pragma once
#include <regex>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fstream>
#include <atomic>
#include <unistd.h>
#include <boost/algorithm/string.hpp>

namespace svr_util {
    const std::string solution_src_path = "/home/shiki/linux_-practice/OnlineJudge/oj_server/solution/src/";
    const std::string solution_bin_path = "/home/shiki/linux_-practice/OnlineJudge/oj_server/solution/bin/";
    const std::string solution_tmp_path = "/home/shiki/linux_-practice/OnlineJudge/oj_server/solution/tmp/";
    const std::string tmp_path = "../compile_server/tmp/";
    //  时间类工具
    class time_util {
    public:
        static std::string get_ms() {
            struct timeval t;
            gettimeofday(&t, nullptr);
            return std::to_string(t.tv_usec * 1000 + t.tv_usec / 1000);
        }
    };
    // 文件路径工具类
    class path_util {
    public:
        // 将传入的待编译文件名加上路径前缀与编译后缀
        static std::string src(const std::string &file_name) {
            std::string src_path = solution_src_path + file_name + ".cc";
            return src_path;
        }
        static std::string exe(const std::string &file_name) {
            std::string exe_path = solution_bin_path + file_name + ".exe";
            return exe_path;
        }
        static std::string err(const std::string &file_name) {
            std::string err_path = solution_tmp_path + file_name + ".err";
            return err_path;
        }
        // 将传入的编译好的文件名加上路径前缀与临时文件后缀
        static std::string Stdin(const std::string &file_name) {
            std::string stdin_path = solution_tmp_path + file_name + ".stdin";
            return stdin_path;
        }
        static std::string Stdout(const std::string &file_name) {
            std::string stdout_path = solution_tmp_path + file_name + ".stdout";
            return stdout_path;
        }
        static std::string Stderr(const std::string &file_name) {
            std::string stderr_path = solution_tmp_path + file_name + ".stderr";
            return stderr_path;
        }
    };

    // 文件读写相关工具类
    class file_util {
    public:
        // 检测文件是否存在
        static bool IsFileExisted(const std::string &file_path) {
            struct stat st;
            if(stat(file_path.c_str(), &st) < 0) return false;
            return true;
        }
        // 获取唯一文件名
        static std::string get_unique_file_name() {
            // 使用原子性自增+毫秒级时间戳保证文件的唯一性
            static std::atomic<uint> i(0);
            ++i;
            std::string unique = time_util::get_ms() + '_' + std::to_string(i);
            return unique;
        }
        // 读写文件
        static bool write_to_file(const std::string &file_path, const std::string &content) {
            std::ofstream out_file(file_path);
            if(!out_file.is_open()) return false;
            out_file.write(content.c_str(), content.size());
            out_file.close();
            return true;
        }
        static bool read_from_file(const std::string &file_path, std::string *content, bool keep = true) {
            content->clear();
            std::ifstream in_file(file_path);
            if(!in_file.is_open()) return false;
            std::string line;
            while(getline(in_file, line)) {
                (*content) += line;
                (*content) += keep ? "\n" : "";
            }
            in_file.close();
            return true;
        }
    };

    // 字符串处理工具
    class string_util {
    public:
        static bool parse_string(const std::string &input, std::vector<std::string> *result, const std::string &delim) {
            if(input.empty()) return false;
            boost::split(*result, input, boost::is_any_of(delim.c_str()), boost::algorithm::token_compress_on);
            return true;
        }
    };
}

#endif // __UTIL_HPP
