#pragma once
#include "thread.hpp"
#include "log.hpp"
#include <functional>
using namespace std;

typedef std::function<int(int, int)> func_;

// 消费生产者模型任务类
class Task{
public:
    Task(){}
    Task(int x, int y, func_ func)      // 包含需要处理的两个数据以及一个处理函数，函数由function包装并
    :a(x)
    ,b(y)
    ,function(func)
    {}
    void operator()(const std::string& name) {
        logMessage(WARNING, "thread-%s任务处理完毕: %d + %d = %d\n | %s | %d", name.c_str()
        , a, b, function(a, b), __FILE__, __LINE__);        // FILE标识所在文件，LINE标识所在行
    }
public:
    int a;
    int b;
    func_ function;
};