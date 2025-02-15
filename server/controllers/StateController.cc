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
        if(!config.isMember("RobotState")){
            Json::Value errorResponse;
            errorResponse["status"] = "error";
            errorResponse["message"] = "RobotState not found in configuration";

            auto response = drogon::HttpResponse::newHttpJsonResponse(errorResponse);
            response->setStatusCode(drogon::HttpStatusCode::k404NotFound);
            callback(response);
            return;
        }

        Json::Value robotState = config["RobotState"];

        auto response = drogon::HttpResponse::newHttpJsonResponse(robotState);
        response->setStatusCode(drogon::HttpStatusCode::k200OK);

        callback(response);
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

void StateController::postMessage(const drogon::HttpRequestPtr &req,
               std::function<void(const drogon::HttpResponsePtr &)> &&callback){
    
    Json::Value jsonBody;

    try
    {
        auto requestBody = req->getJsonObject();

        // Проверка что запрос не пустой
        if (requestBody == nullptr) {
            jsonBody["status"] = "error";
            jsonBody["message"] = "Body is required";
            auto response = HttpResponse::newHttpJsonResponse(jsonBody);
            response->setStatusCode(HttpStatusCode::k400BadRequest);
            callback(response);
            return;
        }

        // Проверка что в теле запроса имеется 'message'
        if (!requestBody->isMember("message")) {
            jsonBody["status"] = "error";
            jsonBody["message"] = "Field `message` is required";
            auto response = HttpResponse::newHttpJsonResponse(jsonBody);
            response->setStatusCode(HttpStatusCode::k400BadRequest);
            callback(response);
            return;
        }

        // получение сообщения
        std::string message = requestBody->get("message", "").asString();
      
        std::cout << "Received message: " << message << std::endl;

        jsonBody["status"] = "ok";
        jsonBody["message"] = "Message received: " + message;
        auto response = HttpResponse::newHttpJsonResponse(jsonBody);
        callback(response);
    }

    catch(const std::exception& e)
    {
        jsonBody["status"] = "error";
        jsonBody["message"] = std::string("Error: ") + e.what();
        auto response = HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
        callback(response);
    }
    
    
}

