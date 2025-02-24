#include <iostream>
#include <fstream>

#include <jsoncpp/json/json.h>

namespace sutils{

    Json::Value getConfigMehJsonValues(const std::string& filename);

    void rewriteConfigMehJsonFile(const std::string& filename, const Json::Value& allData);

}