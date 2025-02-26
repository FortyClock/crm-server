#include "gtest/gtest.h"
#include "testClass.h"
#include "../sutils/actionSutils.h"
#include "../sutils/sutils.h"

#include <cstdlib>
#include <jsoncpp/json/json.h>


using namespace actionSUtils;


void ActionSutilsTest::SetUp(){

    std::cout << "Start test...\n";
}

void ActionSutilsTest::TearDown(){

    std::cout << "Finish test...\n";
}

Json::Value ActionSutilsTest::getTMPMehConfigFile(){

    Json::Value config;


    Json::Value map;
    map["size"] = 10;
    Json::Value items;
    for (int i = 0; i < 10; ++i) {
        Json::Value row;
        for (int j = 0; j < 10; ++j) {
            if (i == 3 && j == 2) {
                row.append("Enemy");
            } else {
                row.append("Empty");
            }
        }
        items.append(row);
    }
    map["items"] = items;
    config["map"] = map;


    Json::Value startPosition;
    Json::Value position;
    position["x"] = 3;
    position["y"] = 3;
    startPosition["position"] = position;
    startPosition["faced_to"] = "W";
    config["start_position"] = startPosition;


    Json::Value robotState;
    Json::Value repairStation;
    repairStation["capacity"] = 10;
    repairStation["repair_kit_num"] = 2;
    repairStation["id"] = "repair_unit_001";
    robotState["repair_station"] = repairStation;

    Json::Value gun;
    gun["capacity"] = 100;
    gun["cartridges"] = 50;
    gun["id"] = "gun_001";
    robotState["gun"] = gun;

    Json::Value gunManip;
    gunManip["capacity"] = 100;
    gunManip["id"] = "gun_manip_001";
    robotState["gun_manip"] = gunManip;

    Json::Value grabManip;
    grabManip["capacity"] = 50;
    grabManip["id"] = "grab_manip_001";
    robotState["grab_manip"] = grabManip;

    Json::Value leftLeg;
    leftLeg["capacity"] = 100;
    leftLeg["id"] = "left_leg_001";
    robotState["left_leg"] = leftLeg;

    Json::Value rightLeg;
    rightLeg["capacity"] = 100;
    rightLeg["id"] = "right_leg_001";
    robotState["right_leg"] = rightLeg;

    Json::Value torso;
    torso["capacity"] = 100;
    torso["id"] = "torso_001";
    robotState["torso"] = torso;

    config["robot_state"] = robotState;


    Json::Value intelligenceInf;
    Json::Value intelligencePosition;
    intelligencePosition["x"] = 3;
    intelligencePosition["y"] = 3;
    intelligenceInf["position"] = intelligencePosition;
    intelligenceInf["faced_to"] = "W";
    config["intelligence_inf"] = intelligenceInf;


    return config;
}

