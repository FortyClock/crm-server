#include "gtest/gtest.h"
#include "../sutils/actionSutils.h"

#include <cstdlib>
#include <jsoncpp/json/json.h>


using namespace actionSUtils;


class ActionSutilsTest: public ::testing::Test{


    protected:

        void SetUp() override{

            std::string filepath = std::string(getenv("HOME")) +
                "/crm-server/server/database/test_mehConfig.json";
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
                            "id": "weapon_001"
                        },
                        "gun_manip": {
                            "capacity": 100,
                            "id": "weapon_manipulator_001"
                        },
                        "grab_manip": {
                            "capacity": 100,
                            "id": "grab_manipulator_001"
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

        void TearDown() override{

            std::string filepath = std::string(getenv("HOME")) +
                "/crm-server/server/database/test_mehConfig.json";
            std::remove(filepath.c_str());

        }

        Json::Value loadTestConfig(){

            std::string filepath = std::string(getenv("HOME")) +
                "/crm-server/server/database/test_mehConfig.json";
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
    
};




TEST_F(ActionSutilsTest, GetConfigMehJsonValues_FileExists_ReturnsJson){

    Json::Value configMeh = actionSUtils::getConfigMehJsonValues("mehConfig.json");

    ASSERT_FALSE(configMeh.empty());

}


TEST_F(ActionSutilsTest, CanShooting_InvalidPosition_ThrowsException){

    Json::Value configMeh = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");

    ASSERT_THROW(actionSUtils::canShooting(10, 3, configMeh), std::logic_error);
}


TEST_F(ActionSutilsTest, CanShooting_LookingDoesNotMatch_ThrowsException){

    Json::Value configMeh = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["intelligence_inf"]["faced_to"] = "E";

    ASSERT_THROW(actionSUtils::canShooting(2, 3, configMeh), std::logic_error);
}


TEST_F(ActionSutilsTest, CanShooting_LowTorsoCapacity_ThrowsException){

    Json::Value configMeh = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["torso"]["capacity"] = 20;

    ASSERT_THROW(actionSUtils::canShooting(2, 3, configMeh), std::logic_error);
}


TEST_F(ActionSutilsTest, CanShooting_LowGunCapacity_ThrowsException){

    Json::Value configMeh = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun"]["capacity"] = 20;

    ASSERT_THROW(actionSUtils::canShooting(2, 3, configMeh), std::logic_error);
}


TEST_F(ActionSutilsTest, CanShooting_NoGunManipulator_ThrowsException){

    Json::Value configMeh = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun_manip"] = "Empty";

    ASSERT_THROW(actionSUtils::canShooting(2, 3, configMeh), std::logic_error);
}


TEST_F(ActionSutilsTest, CanShooting_NoCartridges_ThrowsException){

    Json::Value configMeh = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun"]["cartridges"] = 0;

    ASSERT_THROW(actionSUtils::canShooting(2, 3, configMeh), std::logic_error);
}


TEST_F(ActionSutilsTest, CanShooting_LowGunManipulatorCapacity_ThrowsException){

    Json::Value configMeh = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun_manip"]["capacity"] = 20;

    ASSERT_THROW(actionSUtils::canShooting(2, 3, configMeh), std::logic_error);
}



TEST_F(ActionSutilsTest, CanShooting_NoExceptions){

    Json::Value configMeh = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun"]["capacity"] = 100;
    configMeh["robot_state"]["gun"]["cartridges"] = 50;
    configMeh["robot_state"]["torso"]["capacity"] = 100;
    configMeh["robot_state"]["gun_manip"]["capacity"] = 100;

    
    ASSERT_NO_THROW(actionSUtils::canShooting(2, 3, configMeh));
}




TEST_F(ActionSutilsTest, Shooting_Message_KillEnemy){

    Json::Value configMeh = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun"]["capacity"] = 100;
    configMeh["robot_state"]["gun"]["cartridges"] = 50;
    configMeh["robot_state"]["torso"]["capacity"] = 100;
    configMeh["robot_state"]["gun_manip"]["capacity"] = 100;
    
    ASSERT_EQ(actionSUtils::shooting(2, 3, configMeh), "Shot Enemy killed");
}

TEST_F(ActionSutilsTest, Shooting_Message_Shot){

    Json::Value configMeh = actionSUtils::getConfigMehJsonValues("test_mehConfig.json");
    configMeh["robot_state"]["gun"]["capacity"] = 100;
    configMeh["robot_state"]["gun"]["cartridges"] = 50;
    configMeh["robot_state"]["torso"]["capacity"] = 100;
    configMeh["robot_state"]["gun_manip"]["capacity"] = 100;
    configMeh["map"]["items"][3][2] = "Empty";

    
    ASSERT_EQ(actionSUtils::shooting(2, 3, configMeh), "Shot");
}


int main(int argc, char** argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
