
#include <iostream>
#include<string>
#include<algorithm>
#include<boost/asio.hpp>
#include<boost/json.hpp>
#include<json/json.h>
#include<boost/beast.hpp>
#include"http_server.h"
#include<fstream>
#include"configMgr.h"
int main()
{
    Json::Value root;

    Json::FastWriter fast;
    root["ModuleType"] = Json::Value("ÄãºÃ");
    root["ModuleCode"] = Json::Value("22");
    root["ModuleDesc"] = Json::Value("33");
    root["DateTime"] = Json::Value("44");
    root["LogType"] = Json::Value("55");
    std::cout << fast.write(root) << std::endl;
    configMgr con;
    std::cout << "Config file loaded" << std::endl;
    boost::asio::io_context ioc;

    http_server* server = new http_server(ioc, atoi(con["port"].c_str()));
    server->start_accept();
    ioc.run();
    std::cout << "Server started" << std::endl;
    while (1);

}
