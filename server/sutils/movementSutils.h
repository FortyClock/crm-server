#pragma once

#include "jsoncpp/json/json.h"

namespace movementSutils{

    void canMove(int x, int y, Json::Value allData);
    
    void canTurn(std::string turn, Json::Value allData);
    
    void moving(int x, int y, Json::Value& mehConfig);

    void turning(std::string turn, Json::Value& mehConfig);

}