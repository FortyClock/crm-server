#include <iostream>
#include <fstream>
#include <cstdlib>

#include "movementSutils.h"


namespace movementSutils{

    void canMove(int x, int y, Json::Value allData){

        // берем текущую позицию робота    
        int xPosition = allData["IntelligenceState"]["position"]["x"].asInt();
        int yPosition = allData["IntelligenceState"]["position"]["y"].asInt();

        // ошибка если позиция не является соседней
        if((abs(x - xPosition) > 1 && y - yPosition != 0) ||
           (x - xPosition != 0 && abs(y - yPosition) > 1))
            throw std::logic_error("Not a neighboring cell!")

        // ошибка если позиция вне карты РАБОТА ВЕДЕТСЯ
        
    }
}