#include "gtest/gtest.h"
#include "../sutils/actionSutils.h"
#include "testClass.h"

#include <iostream>
#include <cstdlib>
#include <jsoncpp/json/json.h>


using namespace actionSUtils;


TEST_F(ActionSutilsTest, findStateNameWithId_StateNotFound){

    Json::Value mehCofig = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");

    ASSERT_THROW(
        actionSUtils::findStateNameWithId("bigGun_wp001", mehCofig["robot_state"]),
        std::logic_error
    );

}


TEST_F(ActionSutilsTest, findStateNameWithId_NoException){

    Json::Value mehCofig = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");

    ASSERT_NO_THROW(
        actionSUtils::findStateNameWithId("left_leg_001", mehCofig["robot_state"])
    );

}


TEST_F(ActionSutilsTest, canRepairing_TorsoIsBroke_ThrowException){

    Json::Value mehCofig = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");

    mehCofig["robot_state"]["torso"]["capacity"] = 15;

    ASSERT_THROW(
        actionSUtils::canRepairing("torso_001", mehCofig["robot_state"]),
        std::logic_error
    );

}


TEST_F(ActionSutilsTest, canRepairing_NoRepairKits_ThrowException){

    Json::Value mehCofig = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");

    mehCofig["robot_state"]["repair_station"]["repair_kit_num"] = 0;
    mehCofig["robot_state"]["torso"]["capacity"] = 70;

    ASSERT_THROW(
        actionSUtils::canRepairing("torso_001", mehCofig["robot_state"]),
        std::logic_error
    );

}


TEST_F(ActionSutilsTest, canRepairing_FullCapasity_ThrowException){

    Json::Value mehCofig = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");

    mehCofig["robot_state"]["torso"]["capacity"] = 100;

    ASSERT_THROW(
        actionSUtils::canRepairing("torso_001", mehCofig["robot_state"]),
        std::logic_error
    );

}


TEST_F(ActionSutilsTest, repairSuccessfulRepair){

    Json::Value mehCofig = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");

    mehCofig["robot_state"]["torso"]["capacity"] = 90;
    mehCofig["robot_state"]["repair_station"]["capacity"] = 10;


    actionSUtils::repairing("torso_001", mehCofig);

    ASSERT_EQ(
        mehCofig["robot_state"]["torso"]["capacity"].asInt(),
        100
    );
}