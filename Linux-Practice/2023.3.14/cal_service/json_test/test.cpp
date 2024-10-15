#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
using namespace  std;

int main() {
    int a = 1, b = 2;
    char op = '+';
    // 直接定义json
    Json::Value key;
    key["x"] = a;
    key["y"] = b;
    key["opt"] = op;

    // json套json用法
    Json::Value sub;
    sub["addon"] = 10;
    sub["addon2"] = "surplus";

    key["plus"] = sub;

    // Json::StyledWriter writer;      // 格式化数据转序列（有格式的输出）
    Json::FastWriter writer;            // 直接序列化输出（更精简），并根据字典序排序
    string s = writer.write(key);
    cout << "json序列化为: " << s;

    Json::Value root;
    Json::Reader reader;
    reader.parse(s, root);
    int x = root["x"].asInt();
    int y = root["y"].asInt();
    char ope = root["opt"].asInt();
    printf("json反序列化为: x = %d, y = %d, op = %c\n", x, y, ope);
    return 0;
}