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

            throw std::logic_error("broke_gun_manip");
        }
    
    
        Json::Value intelInf = mehConfig["intelligence_inf"];
        int xPosition = intelInf["position"]["y"].asInt();
        int yPosition = intelInf["position"]["x"].asInt();

    
        // та же позиция или не в пределах карты и не в 3х клетках от меха
        if((xPosition == x && yPosition == y) || 
            (x < 0 && x > 9) && (y < 0 && y > 9) ||
            (abs(x - xPosition) > 3 && abs(y - yPosition) > 3)){
    
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
    
    Json::Value getConfigMehJsonValues(const std::string& filename){
    
        Json::Value allData;
    
        std::ifstream configMehFile(
            std::string(getenv("HOME")) + "/crm-server/server/database/" +
            filename, std::ifstream::binary);
        if(!configMehFile.is_open()){
    
            throw std::runtime_error("Can't open the file");
        }
    
        configMehFile >> allData;
    
        configMehFile.close();
        
        if(allData.empty()){
            throw std::runtime_error("File is empty");
        }
    
        return allData;
    
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
    
    void rewriteJsonFile(const std::string& filename, const Json::Value& allData) {
        
        std::ofstream newMehConfigFile(
            std::string(getenv("HOME")) + "/crm-server/server/database/" + filename);
        if(newMehConfigFile.is_open()){
    
            newMehConfigFile << allData;
            newMehConfigFile.close();
        }
        else{
    
            throw std::runtime_error("Can't open file for rewriting");
        }
    }    

}

