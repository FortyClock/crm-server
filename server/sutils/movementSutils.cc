#include <iostream>
#include <fstream>
#include <cstdlib>

#include "movementSutils.h"
#include "sutils.h"


namespace movementSutils{

    void canMove(int x, int y, Json::Value allData){

        int mapSize = allData["map"]["size"].asInt();

        // берем текущую позицию робота    
        int xPosition = allData["intelligence_inf"]["position"]["y"].asInt();
        int yPosition = allData["intelligence_inf"]["position"]["x"].asInt();


        // ошибка если не верно указана позиция
        if((abs(x - xPosition) > 1 && y - yPosition != 0) ||
           (x - xPosition != 0 && abs(y - yPosition) > 1) ||
           (x >= mapSize || y >= mapSize))
                throw std::logic_error("The position is wrong");
        
    }
}