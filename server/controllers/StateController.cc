#include "StateController.h"
#include "sutils.h"
#include "jsoncpp/json/json.h"
#include <iostream>
#include <fstream>

void StateController::getState(const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback){

    try
    {
        Json::Value config = sutils::getConfigMehJsonValues("mehConfig-example.json");    // конфигурация меха

        // ошибка, если RobotState или IntelligenceState не найдены в конфигурации меха
        if(!config.isMember("robot_state") || !config.isMember("intelligence_inf")){
            Json::Value errorResponse;
            errorResponse["status"] = "error";
            errorResponse["message"] = "robot_state or intelligence_inf not found in configuration";

            auto response = drogon::HttpResponse::newHttpJsonResponse(errorResponse);
            response->setStatusCode(drogon::HttpStatusCode::k404NotFound);
            callback(response);
            return;
        }

        // извлекаем RobotState и IntelligenceState
        Json::Value robotState = config["robot_state"];
        Json::Value intelligenceState = config["intelligence_inf"];

        // комбинируем 
        Json::Value allState;
        allState["robot_state"] = robotState;
        allState["intelligence_inf"]= intelligenceState;
        

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


