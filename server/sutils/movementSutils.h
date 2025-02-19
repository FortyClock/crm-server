#pragma once

#include "jsoncpp/json/json.h"

namespace movementSutils{

    void canMove(Json::Value& position);

    Json::Value getConfigMehJsonValues(const std::string& filename);

    std::string moving(int x, int y, Json::Value& mehConfig);

    void rewriteJsonFile(const std::string& filename, const Json::Value& allData);
}