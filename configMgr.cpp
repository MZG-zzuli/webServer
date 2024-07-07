//
// Created by M on 24-7-6.
//

#include "configMgr.h"



configMgr::configMgr() {
    std::ifstream f;
    boost::filesystem::path path=boost::filesystem::current_path();
    path=path/"config.json";
    f.open(path.string(),std::ios::in);
    Json::Reader re;
    re.parse(f,value);
    if (value["root"]==Json::nullValue)
    {
        value["root"] = boost::filesystem::current_path().string();
    }


}

std::string configMgr::operator[](std::string key) {
    return value[key].asString();
}
