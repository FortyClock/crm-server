#include "gtest/gtest.h"
#include "testClass.h"
#include "../sutils/actionSutils.h"
#include "../sutils/sutils.h"

#include <cstdlib>
#include <jsoncpp/json/json.h>


using namespace actionSUtils;


void ActionSutilsTest::SetUp(){

    std::string filepath = std::string(getenv("CRM_SERVER_DB_DIR")) + "test_mehConfig.json";
    std::ofstream configFile(filepath);
    if(configFile.is_open()){
        configFile << R"({
            "map": {
                "size": 10,
                "items": [
                    ["Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty"],
                    ["Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty"],
                    ["Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty"],
                    ["Empty", "Empty", "Enemy", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty"],
                    ["Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty"],
                    ["Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty"],
                    ["Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty"],
                    ["Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty"],
                    ["Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty"],
                    ["Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty"]
                ]
            },
            "start_position": {
                "position": {
                    "x": 3,
                    "y": 3
                },
                "faced_to": "W"
            },
            "robot_state": {
                "repair_station": {
                    "capacity": 10,
                    "repair_kit_num": 2,
                    "id": "repair_unit_001"
                },
                "gun": {
                    "capacity": 100,
                    "cartridges": 50,
                    "id": "gun_001"
                },
                "gun_manip": {
                    "capacity": 100,
                    "id": "gun_manip_001"
                },
                "grab_manip": {
                    "capacity": 50,
                    "id": "grab_manip_001"
                },
                "left_leg": {
                    "capacity": 100,
                    "id": "left_leg_001"
                },
                "right_leg": {
                    "capacity": 100,
                    "id": "right_leg_001"
                },
                "torso": {
                    "capacity": 100,
                    "id": "torso_001"
                }
            },
            "intelligence_inf": {
                "position": {
                    "x": 3,
                    "y": 3
                },
                "faced_to": "W"
            }
        })";
        configFile.close();

    }
    else{

        throw std::runtime_error("Can't open file (test class) " + filepath);
    
    }

}

void ActionSutilsTest::TearDown(){

    std::string filepath = std::string(getenv("CRM_SERVER_DB_DIR")) + "test_mehConfig.json";
    std::remove(filepath.c_str());

}

Json::Value ActionSutilsTest::loadTestConfig(){

    std::string filepath = std::string(getenv("CRM_SERVER_DB_DIR")) + "test_mehConfig.json";
    Json::Value config;
    std::ifstream configFile(filepath);
    if(configFile.is_open()){

        configFile >> config;
        configFile.close();

    }
    else{

        throw std::runtime_error("Can't open file (test class)");
    
    }

    return config;

}