#include <iostream>
#include <fstream>
#include <cstdlib>

#include "actionSutils.h"
#include <jsoncpp/json/json.h>


namespace actionSUtils{    



    void canShooting(int x, int y, Json::Value& mehConfig){

        if(mehConfig["robot_state"]["torso"]["capacity"].asInt() <= 20){
            
            throw std::logic_error("low torso capacity");
        }
        else if(mehConfig["robot_state"]["gun"]["capacity"].asInt() <= 20){
    
            throw std::logic_error("low gun capacity");
        }
    
        if(mehConfig["robot_state"]["gun_manip"] == "Empty"){
    
            throw std::logic_error("no gun manipulator");
        }
    
        if(mehConfig["robot_state"]["gun"]["cartridges"].asInt() == 0){
            
            throw std::logic_error("no cartridges");
        }
    
        if(mehConfig["robot_state"]["gun_manip"]["capacity"].asInt() <= 20){

            mehConfig["robot_state"]["gun_manip"] = "Empty";
            
            if(mehConfig["robot_state"]["torso"]["capacity"].asInt() <= 50){
                
                mehConfig["robot_state"]["torso"]["capacity"] = 0;
            }
            else{
                
                mehConfig["robot_state"]["torso"]["capacity"] =
                    mehConfig["robot_state"]["torso"]["capacity"].asInt() - 50;
            }

            throw std::logic_error("broke_gun_manip");
        }
    
    
        Json::Value intelInf = mehConfig["intelligence_inf"];
        int xPosition = intelInf["position"]["x"].asInt();
        int yPosition = intelInf["position"]["y"].asInt();
        int size = mehConfig["map"]["size"].asInt();
        

    
        // та же позиция или не в пределах карты и не в 3х клетках от меха
        if((xPosition == x && yPosition == y) || 
            (x < 0 || x > size) || (y < 0 || y > size) ||
            (abs(x - xPosition) > 3 || abs(y - yPosition) > 3)){
    
            throw std::logic_error("Invalid position");
        }
    
    
        // проверяем возможность стрельбы по положению
        if((intelInf["faced_to"] == "N" && !(xPosition == x && yPosition > y)) ||
            (intelInf["faced_to"] == "S" && !(xPosition == x && yPosition < y)) ||
            (intelInf["faced_to"] == "W" && !(xPosition > x && yPosition == y)) ||
            (intelInf["faced_to"] == "E" && !(xPosition < x && yPosition == y))){
            
            throw std::logic_error("Looking doesn't match");
        }
    
    }
    
    std::string shooting(int x, int y, Json::Value& mehConfig){
    
        std::string message;
    
        mehConfig["robot_state"]["gun"]["capacity"] = 
            mehConfig["robot_state"]["gun"]["capacity"].asInt() - 10;
        
        mehConfig["robot_state"]["gun"]["cartridges"] = 
            mehConfig["robot_state"]["gun"]["cartridges"].asInt() - 1;
    
        mehConfig["robot_state"]["gun_manip"]["capacity"] = 
            mehConfig["robot_state"]["gun_manip"]["capacity"].asInt() - 5;
    
        mehConfig["robot_state"]["torso"]["capacity"] = 
            mehConfig["robot_state"]["torso"]["capacity"].asInt() - 1;
    
    
        if(mehConfig["map"]["items"][y][x] == "Empty"){
    
            message = "Shot";
            return message;
        }
        mehConfig["map"]["items"][y][x] = "Empty";
        message = "Shot Enemy killed";

        std::cout << message << std::endl;
    
        return message;
    
    }
    
    

    std::string findStateNameWithId(const std::string &id, Json::Value& RobotState){

        size_t position = id.find_last_of('_');

        if(position == std::string::npos){

            throw std::logic_error("State (" + id + ") not found");
        }

        std::string stateName = id.substr(0, position);

        if(RobotState[stateName].isNull() || RobotState[stateName] == "Empty"){

            throw std::logic_error("State (" + id + ") not found");
        }

        return stateName;

    }

    void canRepairing(const std::string &id, Json::Value& RobotState){

        if(RobotState["torso"]["capacity"] <= 20){

            throw std::logic_error("Can't repair, torso is broke");
        }

        if(RobotState["repair_station"]["repair_kit_num"] <= 0){

            throw std::logic_error("No repair kits");
        }

        std::string stateName = findStateNameWithId(id, RobotState);

        if(RobotState[stateName]["capacity"] == 100){

            throw std::logic_error("Capacity (" + id + ") is full");
        }

    }

    void repairing(const std::string &id, Json::Value& mehConfig){

        std::string stateName = findStateNameWithId(id, mehConfig["robot_state"]);
        int stateCapacity = mehConfig["robot_state"][stateName]["capacity"].asInt();
        int capacityWillRepaired = mehConfig["robot_state"]["repair_station"]["capacity"].asInt();

        if(stateCapacity + capacityWillRepaired >= 100){
            stateCapacity = 100;
        }
        else{
            stateCapacity += capacityWillRepaired;
        }

        mehConfig["robot_state"][stateName]["capacity"] = stateCapacity;
        mehConfig["robot_state"]["repair_station"]["repair_kit_num"] = 
            mehConfig["robot_state"]["repair_station"]["repair_kit_num"].asInt() - 1;

    }

}

