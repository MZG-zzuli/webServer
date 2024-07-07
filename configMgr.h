//
// Created by M on 24-7-6.
//

#ifndef BEASTLOVE_CONFIGMGR_H
#define BEASTLOVE_CONFIGMGR_H

#include<fstream>
#include<iostream>
#include<json/json.h>
#include<boost/filesystem.hpp>
class configMgr {
private:
    Json::Value value;

public:
    configMgr();
    std::string operator[](std::string key);
};


#endif //BEASTLOVE_CONFIGMGR_H
