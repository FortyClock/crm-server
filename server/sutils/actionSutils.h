#include <iostream>
#include <fstream>

#include <jsoncpp/json/json.h>

namespace actionSUtils{

    void canShooting(int x, int y, Json::Value& intelState);

    Json::Value getConfigMehJsonValues(const std::string& filename);

    std::string shooting(int x, int y, Json::Value& mehConfig);

    void rewriteJsonFile(const std::string& filename, const Json::Value& allData);

}