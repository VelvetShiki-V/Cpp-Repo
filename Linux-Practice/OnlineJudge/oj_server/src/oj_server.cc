#include "../include/oj_server.hpp"
using namespace httplib;

int main() {
    Server server;
    svr_controller::controller ctrl;
    // 用户请求获取题目列表
    server.Get("/listall", [&ctrl](const Request &req, Response &res){
        std::string html;
        ctrl.get_question_list(&html);
        res.set_content(html, "text/html;charset=utf-8");   
    });

    // 用户请求题目编号对应内容，\d+正则表达式来匹配对应的题目编号，match从请求报文中取出内容
    server.Get(R"(/problem/(\d+))", [&ctrl](const Request &req, Response &res){
        std::string html;
        std::string prob_index = req.matches[1];        // 1号下标正则内容
        ctrl.get_certain_question(prob_index, &html);
        res.set_content(html, "text/html;charset=utf-8");
    });
    // 用户提交代码，判题，编译，运行服务
    server.Get(R"(/judge/(\d+))", [&ctrl](const Request &req, Response &res){
        std::string prob_index = req.matches[1];        // 1号下标正则内容
    });
    // 设定默认主页（不发送任何请求即转到该页面）
    server.set_base_dir("/home/shiki/linux_-practice/OnlineJudge/oj_server/wwwroot");
    server.listen("0.0.0.0", 8082);
    return 0;
}