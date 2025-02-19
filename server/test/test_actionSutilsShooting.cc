#include "gtest/gtest.h"
#include "../sutils/actionSutils.h"
#include "../sutils/sutils.h"
#include "testClass.h"

#include <cstdlib>
#include <jsoncpp/json/json.h>


using namespace actionSUtils;
using namespace sutils;


TEST_F(ActionSutilsTest, GetConfigMehJsonValues_FileExists_ReturnsJson){

    Json::Value configMeh = sutils::getConfigMehJsonValues("mehConfig.json");

    ASSERT_FALSE(configMeh.empty());

}


TEST_F(ActionSutilsTest, CanShooting_InvalidPosition_ThrowsException){

    Json::Value configMeh = sutils::getConfigMehJsonValues("test_mehConfig.json");

    ASSERT_THROW(actionSUtils::canShooting(10, 3, configMeh), std::logic_error);
}


TEST_F(ActionSutilsTest, CanShooting_LookingDoesNotMatch_ThrowsException){

    Json::Value configMeh = sutils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["intelligence_inf"]["faced_to"] = "E";

    ASSERT_THROW(actionSUtils::canShooting(2, 3, configMeh), std::logic_error);
}


TEST_F(ActionSutilsTest, CanShooting_LowTorsoCapacity_ThrowsException){

    Json::Value configMeh = sutils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["torso"]["capacity"] = 20;

    ASSERT_THROW(actionSUtils::canShooting(2, 3, configMeh), std::logic_error);
}


TEST_F(ActionSutilsTest, CanShooting_LowGunCapacity_ThrowsException){

    Json::Value configMeh = sutils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun"]["capacity"] = 20;

    ASSERT_THROW(actionSUtils::canShooting(2, 3, configMeh), std::logic_error);
}


TEST_F(ActionSutilsTest, CanShooting_NoGunManipulator_ThrowsException){

    Json::Value configMeh = sutils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun_manip"] = "Empty";

    ASSERT_THROW(actionSUtils::canShooting(2, 3, configMeh), std::logic_error);
}


TEST_F(ActionSutilsTest, CanShooting_NoCartridges_ThrowsException){

    Json::Value configMeh = sutils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun"]["cartridges"] = 0;

    ASSERT_THROW(actionSUtils::canShooting(2, 3, configMeh), std::logic_error);
}


TEST_F(ActionSutilsTest, CanShooting_LowGunManipulatorCapacity_ThrowsException){

    Json::Value configMeh = sutils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun_manip"]["capacity"] = 20;

    ASSERT_THROW(actionSUtils::canShooting(2, 3, configMeh), std::logic_error);
}



TEST_F(ActionSutilsTest, CanShooting_NoExceptions){

    Json::Value configMeh = sutils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun"]["capacity"] = 100;
    configMeh["robot_state"]["gun"]["cartridges"] = 50;
    configMeh["robot_state"]["torso"]["capacity"] = 100;
    configMeh["robot_state"]["gun_manip"]["capacity"] = 100;

    
    ASSERT_NO_THROW(actionSUtils::canShooting(2, 3, configMeh));
}




TEST_F(ActionSutilsTest, Shooting_Message_KillEnemy){

    Json::Value configMeh = sutils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun"]["capacity"] = 100;
    configMeh["robot_state"]["gun"]["cartridges"] = 50;
    configMeh["robot_state"]["torso"]["capacity"] = 100;
    configMeh["robot_state"]["gun_manip"]["capacity"] = 100;
    
    ASSERT_EQ(actionSUtils::shooting(2, 3, configMeh), "Shot Enemy killed");
}

TEST_F(ActionSutilsTest, Shooting_Message_Shot){

    Json::Value configMeh = sutils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun"]["capacity"] = 100;
    configMeh["robot_state"]["gun"]["cartridges"] = 50;
    configMeh["robot_state"]["torso"]["capacity"] = 100;
    configMeh["robot_state"]["gun_manip"]["capacity"] = 100;
    configMeh["map"]["items"][3][2] = "Empty";

    
    ASSERT_EQ(actionSUtils::shooting(2, 3, configMeh), "Shot");
}

