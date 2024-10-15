#ifndef __MODEL_HPP
#define __MODEL_HPP
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>
#include "../../comm/log.hpp"
#include "../../comm/util.hpp"
#define SPACE " "

namespace svr_model {
    using namespace svr_util;
    using namespace svr_log;
    const std::string question_list_path = "/home/shiki/linux_-practice/OnlineJudge/oj_server/question_list.txt";
    const std::string question_path = "/home/shiki/linux_-practice/OnlineJudge/oj_server/question/";

    // 题目描述类
    class question {
    public:
        std::string index;
        std::string title;
        std::string difficulty;
        int cpu_limit;
        int memory_limit;
        std::string describe;
        std::string header;
        std::string tail;
    };

    class model {
    public:
        // 根据题目列表配置文件将合法题目load到内存中
        bool load_question_list(const std::string &qustion_list_file) {
            // 检查题目列表配置文件合法性，并打开文件逐行解析
            if(file_util::IsFileExisted(qustion_list_file)) {
                std::ifstream in_file(qustion_list_file);
                if(in_file.is_open()) {
                    std::string line;
                    std::vector<std::string> tokens;
                    while(getline(in_file, line)) {
                        // 每行内容以空格分割，插入数组中
                        string_util::parse_string(line, &tokens, SPACE);
                        if(tokens.size() != 5) {
                            LOG(ERROR) << "question line parse failed: " << line << std::endl;
                            continue;
                        }
                        // 获取到合法题目描述，转换成结构化数据
                        question q;
                        q.index = tokens[0];
                        q.title = tokens[1];
                        q.difficulty = tokens[2];
                        q.cpu_limit = std::stoi(tokens[3]);
                        q.memory_limit = std::stoi(tokens[4]);
                        // header和tail，describe单独处理，读取文件到字段中
                        std::string config_path = question_path + 'q' + q.index + '/';
                        if(!file_util::read_from_file(config_path + "header.cc", &q.header)) {
                            LOG(FATAL) << config_path + "header.cc read failed" << std::endl;
                            in_file.close();
                            return false;
                        }
                        if(!file_util::read_from_file(config_path + "tail.cc", &q.tail)) {
                            LOG(FATAL) << config_path + "tail.cc read failed" << std::endl;
                            in_file.close();
                            return false;
                        }
                        if(!file_util::read_from_file(config_path + "describe.txt", &q.describe)) {
                            LOG(FATAL) << config_path + "describe.txt read failed" << std::endl;
                            in_file.close();
                            return false;
                        }
                        // 将解析完成为结构化数据的题目列表添加到题目编号映射中
                        _question_map[q.index] = q;
                    }
                    LOG(INFO) << "question list load success" << std::endl;
                    in_file.close();
                    return true;
                }
                else {
                    LOG(FATAL) << "question list open failed" << std::endl;
                }
            }
            else {
                LOG(FATAL) << "question list file is not existed" << std::endl;
            }
            return false;
        }

        // 用户请求获得所有题库
        bool get_all_questions(std::vector<question> *q) {
            if(_question_map.size() == 0) {
                LOG(ERROR) << "question fetched failed, empty question list presented" << std::endl;
                return false;
            }
            for(const auto& question: _question_map) {
                q->emplace_back(question.second);
            }
            return true;
        }

        // 用户请求获得某一道题目
        bool get_one_question(const std::string &index, question *q) {
            auto iter = _question_map.find(index);
            if(iter != _question_map.end()) {
                // 找到
                *q = iter->second;
                return true;
            }
            else {
                LOG(ERROR) << "question fetched failed, question not exists" << std::endl;
            }
            return false;
        }

        // 初始化model，将题目列表加载到内存中
        model() {
            assert(load_question_list(question_list_path));
        }

    private:
        std::unordered_map<std::string, question> _question_map;
    };
}

#endif  // __MODEL_HPP