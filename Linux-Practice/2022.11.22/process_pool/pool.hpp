#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <ctime>
#include <unistd.h>
#include <functional>
#include <unordered_map>
#include <sys/types.h>
#include <sys/wait.h>
#include <cassert>
using namespace std;
#define PROCESS_NUMS 5

// 数组v用于存储不同功能的函数接口，便于后续子进程接收任务时根据任务编号执行对应功能
vector<function<void()>> v;
// 哈希表description用于描述子进程接收到的order为何种指令，需要执行何种任务
unordered_map<int, string> description;

void arguments_analysis() {
    cout << " [参数包解析任务]\n" << endl;
}
void mysql_connection() {
    cout << " [mysql数据库链接任务]\n" << endl;
}
void data_visualization() {
    cout << " [数据可视化任务]\n" << endl;
}
void website_redirection() {
    cout << " [站点跳转任务]\n" << endl;
}
void dq_autosolution() {
    cout << " [动态规划自动寻优任务]\n" << endl;
}

void load() {
    v.emplace_back(arguments_analysis);
    description.emplace(0, "arguments_analysis");
    v.emplace_back(mysql_connection);
    description.emplace(1, "mysql_connection");
    v.emplace_back(data_visualization);
    description.emplace(2, "data_visualization");
    v.emplace_back(website_redirection);
    description.emplace(3, "website_redirection");
    v.emplace_back(dq_autosolution);
    description.emplace(4, "dq_autosolution");
}

size_t size() {
    return v.size();
}