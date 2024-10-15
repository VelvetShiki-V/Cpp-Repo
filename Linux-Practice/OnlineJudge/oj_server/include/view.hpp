#ifndef __VIEW_HPP
#define __VIEW_HPP
#pragma once

#include <iostream>
#include <ctemplate/template.h>
#include <string>
#include "model.hpp"

namespace svr_view {
    using namespace svr_model;
    static const std::string template_path = "/home/shiki/linux_-practice/OnlineJudge/oj_server/template_html/";
    class view{
    public:
        // 题目列表网页渲染生成
        bool list_web_expand(const std::vector<question> &v, std::string *html) {
            // 设置需要渲染的网页路径
            std::string src_html = template_path + "question_list.html";
            // 生成数据字典
            ctemplate::TemplateDictionary root("question_list");
            for(const auto &all: v) {
                // 设置渲染字段映射
                ctemplate::TemplateDictionary *sub = root.AddSectionDictionary("list");     // 循环渲染
                sub->SetValue("index", all.index);
                sub->SetValue("title", all.title);
                sub->SetValue("difficulty", all.difficulty);
            }
            // 获取需要被渲染的网页内容
            ctemplate::Template *tpl = ctemplate::Template::GetTemplate(src_html, ctemplate::DO_NOT_STRIP);
            // 添加字段数据到网页中进行渲染
            if(tpl->Expand(html, &root)) return true;
            else {
                *html = "渲染失败";
                return false;
            }
        }

        // 单个题目详细信息网页渲染生成
        bool certain_web_expand(const question &q, std::string *html) {
            std::string src_html = template_path + "get_single_question.html";
            ctemplate::TemplateDictionary root("get_single_question");
            root.SetValue("index", q.index);
            root.SetValue("title", q.title);
            root.SetValue("difficulty", q.difficulty);
            root.SetValue("describe", q.describe);
            root.SetValue("code_area", q.header);
            ctemplate::Template *tpl = ctemplate::Template::GetTemplate(src_html, ctemplate::DO_NOT_STRIP);
            if(tpl->Expand(html, &root)) return true;
            else {
                *html = "渲染失败";
                return false;
            }
        }
    };
}
#endif  // __VIEW_HPP