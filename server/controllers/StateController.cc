#include "StateController.h"
#include "jsoncpp/json/json.h"
#include <iostream>
#include <fstream>

//check
//hello


Json::Value StateController::loadConfig()
{
    Json::Value config;
    std::ifstream configFile("../database/mehConfig.json");

    if(configFile.is_open()){
        configFile >> config;
        configFile.close();
    } 
    
    else {
        std::cerr << "Error: Unable to open config file!" << std::endl;
        config["error"] = "Unable to open config file!";
    }

    return config;
}

void StateController::getState(const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback){

    try
    {
        Json::Value config = loadConfig();    // конфигурация меха

        // ошибка, если ключ RobotState не найден в конфигурации меха
        if(!config.isMember("RobotState") || !config.isMember("IntelligenceState")){
            Json::Value errorResponse;
            errorResponse["status"] = "error";
            errorResponse["message"] = "RobotState or IntelligenceState not found in configuration";

            auto response = drogon::HttpResponse::newHttpJsonResponse(errorResponse);
            response->setStatusCode(drogon::HttpStatusCode::k404NotFound);
            callback(response);
            return;
        }

        //извлекаем RobotState и "IntelligenceState" 
        Json::Value robotState = config["RobotState"];
        Json::Value intelligenceState = config["IntelligenceState"];

        Json::Value allState;
        allState["RobotState"] = robotState;
        allState["IntelligenceState"]= intelligenceState;
        

        auto responseAllState = drogon::HttpResponse::newHttpJsonResponse(allState);
        //auto responseIntelligenceState = drogon::HttpResponse::newHttpJsonResponse(intelligenceState);

        responseAllState->setStatusCode(drogon::HttpStatusCode::k200OK);
        //responseIntelligenceState->setStatusCode(drogon::HttpStatusCode::k200OK);

        callback(responseAllState);
        //callback(responseIntelligenceState);
    }
    catch(const std::exception& e)
    {
        Json::Value err;
        err["error"] = e.what();

        auto response = drogon::HttpResponse::newHttpJsonResponse(err);
        response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);

        callback(response);
    }
    

}


