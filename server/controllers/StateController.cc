#include "StateController.h"
#include "sutils.h"
#include "jsoncpp/json/json.h"
#include <iostream>
#include <fstream>

void StateController::getState(const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback){

    try
    {
        Json::Value config = sutils::getConfigMehJsonValues();    // конфигурация меха

        // ошибка, если RobotState или IntelligenceState не найдены в конфигурации меха
        if(!config.isMember("RobotState") || !config.isMember("IntelligenceState")){
            Json::Value errorResponse;
            errorResponse["status"] = "error";
            errorResponse["message"] = "RobotState or IntelligenceState not found in configuration";

            auto response = drogon::HttpResponse::newHttpJsonResponse(errorResponse);
            response->setStatusCode(drogon::HttpStatusCode::k404NotFound);
            callback(response);
            return;
        }

        // извлекаем RobotState и IntelligenceState 
        Json::Value robotState = config["RobotState"];
        Json::Value intelligenceState = config["IntelligenceState"];

        // комбинируем 
        Json::Value allState;
        allState["RobotState"] = robotState;
        allState["IntelligenceState"]= intelligenceState;
        

        auto responseAllState = drogon::HttpResponse::newHttpJsonResponse(allState);
        responseAllState->setStatusCode(drogon::HttpStatusCode::k200OK);

        callback(responseAllState);
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


