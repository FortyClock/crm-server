#pragma once

#include "jsoncpp/json/json.h"

namespace movementSutils{

    std::string moving(int x, int y, Json::Value& mehConfig);
}