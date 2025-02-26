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

        // текущая позиция робота    
        int xPosition = mehConfig["intelligence_inf"]["position"]["x"].asInt();
        int yPosition = mehConfig["intelligence_inf"]["position"]["y"].asInt();

        if (mehConfig["robot_state"]["torso"]["capacity"].asInt() <= 20)
            throw std::logic_error("low torso capicity");


        std::string facedTo = mehConfig["intelligence_inf"]["faced_to"].asString();


        if(facedTo == "N" || facedTo == "S"){
            if(xPosition == x){ // движение вперед или назад
                if(mehConfig["robot_state"]["left_leg"]["capacity"].asInt() <= 20 || mehConfig["robot_state"]["right_leg"]["capacity"].asInt() <= 20){
                    throw std::logic_error("legs are broken");
                }
                mehConfig["robot_state"]["left_leg"]["capacity"] = mehConfig["robot_state"]["left_leg"]["capacity"].asInt() - 5;
                mehConfig["robot_state"]["right_leg"]["capacity"] = mehConfig["robot_state"]["right_leg"]["capacity"].asInt() - 5;
            } else if(facedTo == "N"){ 
                if(xPosition < x){ // движение вправо
                    if(mehConfig["robot_state"]["right_leg"]["capacity"].asInt() <= 20){
                        throw std::logic_error("low right leg capicity");
                    } 
                    mehConfig["robot_state"]["right_leg"]["capacity"] = mehConfig["robot_state"]["right_leg"]["capacity"].asInt() - 10;
                } else{ // движение влево
                    if(mehConfig["robot_state"]["left_leg"]["capacity"].asInt() <= 20){
                        throw std::logic_error("low left leg capicity");
                    }
                    mehConfig["robot_state"]["left_leg"]["capacity"] = mehConfig["robot_state"]["left_leg"]["capacity"].asInt() - 10;
                } 
                    
            } else{
                if(xPosition > x){ // движение вправо
                    if(mehConfig["robot_state"]["right_leg"]["capacity"].asInt() <= 20){
                        throw std::logic_error("low right leg capicity");
                    }
                    mehConfig["robot_state"]["right_leg"]["capacity"] = mehConfig["robot_state"]["right_leg"]["capacity"].asInt() - 10;
                } else{ // движение влево
                    if(mehConfig["robot_state"]["left_leg"]["capacity"].asInt() <= 20){
                        throw std::logic_error("low left leg capicity");
                    }
                    mehConfig["robot_state"]["left_leg"]["capacity"] = mehConfig["robot_state"]["left_leg"]["capacity"].asInt() - 10;
                } 
                    
            }           
        } else if(yPosition == y){ // движение вперед или назад
            if(mehConfig["robot_state"]["left_leg"]["capacity"].asInt() <= 20 || mehConfig["robot_state"]["right_leg"]["capacity"].asInt() <= 20){
                throw std::logic_error("legs are broken");
            }
            mehConfig["robot_state"]["left_leg"]["capacity"] = mehConfig["robot_state"]["left_leg"]["capacity"].asInt() - 5;
            mehConfig["robot_state"]["right_leg"]["capacity"] = mehConfig["robot_state"]["right_leg"]["capacity"].asInt() - 5;
        } else if(facedTo == "W"){
            if(yPosition < y){ // движение влево
                if(mehConfig["robot_state"]["left_leg"]["capacity"].asInt() <= 20){
                    throw std::logic_error("low left leg capicity");
                }
                mehConfig["robot_state"]["left_leg"]["capacity"] = mehConfig["robot_state"]["left_leg"]["capacity"].asInt() - 10;
            } else{ // движение вправо
                if(mehConfig["robot_state"]["right_leg"]["capacity"].asInt() <= 20){
                    throw std::logic_error("low right leg capicity");
                }
                mehConfig["robot_state"]["right_leg"]["capacity"] = mehConfig["robot_state"]["right_leg"]["capacity"].asInt() - 10;
            }                
        } else{
            if(yPosition > y){ // движение влево
                if(mehConfig["robot_state"]["left_leg"]["capacity"].asInt() <= 20){
                    throw std::logic_error("low left leg capicity");
                }
                mehConfig["robot_state"]["left_leg"]["capacity"] = mehConfig["robot_state"]["left_leg"]["capacity"].asInt() - 10;
            } else{// движение вправо
                if(mehConfig["robot_state"]["right_leg"]["capacity"].asInt() <= 20)
                    throw std::logic_error("low right leg capicity");
                mehConfig["robot_state"]["right_leg"]["capacity"] = mehConfig["robot_state"]["right_leg"]["capacity"].asInt() - 10;
            } 
                
        }

        // Уменьшение прочности торса при любом движении
        mehConfig["robot_state"]["torso"]["capacity"] = mehConfig["robot_state"]["torso"]["capacity"].asInt() - 1;


        mehConfig["intelligence_inf"]["position"]["x"] = x;
        mehConfig["intelligence_inf"]["position"]["y"] = y;
    }

    void turning(std::string turn, Json::Value& mehConfig){

        mehConfig["intelligence_inf"]["faced_to"] = turn;
    }
}