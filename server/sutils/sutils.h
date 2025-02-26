#include <iostream>
#include <fstream>

#include <jsoncpp/json/json.h>

namespace sutils{

    Json::Value getConfigMehJsonValues();

    void rewriteConfigMehJsonFile(const Json::Value& allData);

}