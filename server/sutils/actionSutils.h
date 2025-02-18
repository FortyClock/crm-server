#include <iostream>
#include <fstream>

#include <jsoncpp/json/json.h>

namespace actionSUtils{

    Json::Value getConfigMehJsonValues(const std::string& filename);

    void rewriteJsonFile(const std::string& filename, const Json::Value& allData);



    void canShooting(int x, int y, Json::Value& mehConfig);

    std::string shooting(int x, int y, Json::Value& mehConfig);



    std::string findStateNameWithId(const std::string &id, Json::Value& RobotState);

    void canRepairing(const std::string &id, Json::Value& RobotState);

    void repairing(const std::string &id, Json::Value& mehConfig);

}