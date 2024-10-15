#include <iostream>
#include "httplib.h"
#include "pthread.h"
#include "jsoncpp/json/json.h"

using namespace httplib;
using namespace std;

int main() {
    Server svr;
    cout << "service processing, json string: " << endl;
    svr.Post("", [](const Request &req, Response &resp){
        
        std::string js_string = req.body;
        Json::Value root;
        Json::Reader reader;
        reader.parse(js_string, root);

        int type = root["vehicle_type"].asInt();
        bool cover = root["is_covered"].asBool();
        string plate = root["plate_number"].asString();
        string evidence = root["snapshot_url"].asString();

        cout << "type: " << type << endl;
        cout << "cover: " << cover << endl;
        cout << "plate: " << plate << endl;
        cout << "evidence: " << evidence << endl;

        resp.set_content("info has claimed", "text/plain;charset=utf-8");
     });
    svr.listen("0.0.0.0", 8080);
     
    return 0;
}