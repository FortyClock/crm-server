#include <iostream>
#include <fstream>
#include <cstdlib>

#include "movementSutils.h"
#include "sutils.h"


namespace movementSutils{

    void canMove(int x, int y, Json::Value allData){

        int mapSize = allData["map"]["size"].asInt();

        // берем текущую позицию робота    
        int xPosition = allData["intelligence_inf"]["position"]["x"].asInt();
        int yPosition = allData["intelligence_inf"]["position"]["y"].asInt();


        // ошибка если не верно указана позиция
        if((abs(x - xPosition) > 1 && y - yPosition != 0) ||
           (x - xPosition != 0 && abs(y - yPosition) > 1) ||
           (x >= mapSize || y >= mapSize) ||
           (x < 0 || y < 0))
                throw std::logic_error("The position is wrong");
        
    }

    void moving(int x, int y, Json::Value& mehConfig){

        mehConfig["intelligence_inf"]["position"]["x"] = x;
        mehConfig["intelligence_inf"]["position"]["y"] = y;
    }

}