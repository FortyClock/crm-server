#include <iostream>
#include <fstream>
#include <cstdlib>

#include "movementSutils.h"
#include "sutils.h"


namespace movementSutils{

    void canMove(int x, int y, Json::Value allData){

        int mapSize = allData["map"]["size"].asInt();

        // текущая позиция робота    
        int xPosition = allData["intelligence_inf"]["position"]["x"].asInt();
        int yPosition = allData["intelligence_inf"]["position"]["y"].asInt();


        // ошибка если не верно указана позиция
        if((abs(x - xPosition) > 1 && y - yPosition != 0) ||
           (x - xPosition != 0 && abs(y - yPosition) > 1) ||
           (x >= mapSize || y >= mapSize) ||
           (x < 0 || y < 0))
                throw std::logic_error("The position is wrong");
        
    }


    void canTurn(std::string turn, Json::Value allData){


        //текущее напрвление робота
        std::string facedTo = allData["intelligence_inf"]["faced_to"].asString();

        if((turn == "N" && facedTo == "S" || turn == "S" && facedTo == "N") || 
            (turn == "W" && facedTo == "E" || turn == "E" && facedTo == "W"))
            throw std::logic_error("The turn is wrong");
    }

    void moving(int x, int y, Json::Value& mehConfig){

        mehConfig["intelligence_inf"]["position"]["x"] = x;
        mehConfig["intelligence_inf"]["position"]["y"] = y;
    }

    void turning(std::string turn, Json::Value& mehConfig){

        mehConfig["intelligence_inf"]["faced_to"] = turn;
    }

}