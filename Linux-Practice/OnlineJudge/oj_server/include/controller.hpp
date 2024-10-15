#ifndef __CONTROLLER_HPP
#define __CONTROLLER_HPP
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "model.hpp"
#include "view.hpp"
#include "../../comm/log.hpp"
#include "../../comm/util.hpp"

namespace svr_controller {
    using namespace svr_util;
    using namespace svr_model;
    using namespace svr_log;
    using namespace svr_view;

    class controller {
    public:
        // 从model中获取题目列表，并通过view进行网页渲染
        bool get_question_list(std::string *html) {
            std::vector<question> v;
            if(!m.get_all_questions(&v)) {
                LOG(FATAL) << "request to fetch question list failed" << std::endl;
                return false;
            }
            else {
                // 获取题目列表成功，进行view网页构建并渲染
                vu.list_web_expand(v, html);
            }
            return true;
        }

        // 从model获取单个题目，并view渲染
        bool get_certain_question(const std::string &index, std::string *html) {
            question q;
            if(!m.get_one_question(index, &q)) {
                *html = "request to fetch question index: " + index + "not found";
                return false;
            }
            else {
                // 获取到对应题目，进行view构建网页并渲染
                vu.certain_web_expand(q, html);
            }
            return true;
        }
    private:
        model m;
        view vu;
    };
}

#endif  // __CONTROLLER_HPP