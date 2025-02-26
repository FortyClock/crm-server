#include "MovementController.h"
#include "sutils.h"
#include "movementSutils.h"
#include "jsoncpp/json/json.h"
#include <iostream>

void MovementController :: postPosition(const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback){
    
    Json::Value jsonBody;
   
    auto requestBody = req->getJsonObject();
    
    // Проверка что пришла позиция меха
    if (!requestBody || !requestBody->isMember("x") || !requestBody->isMember("y")) {
        jsonBody["status"] = "error";
        jsonBody["message"] = "Fields 'x' and 'y' are required";
        auto response = HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(HttpStatusCode::k400BadRequest);
        callback(response);
        return;
    }

    // Получение позиции
    int x = requestBody->get("x", "").asInt();
    int y = requestBody->get("y", "").asInt();

    std::cout << "Received position " << x << ", " << y << std::endl;

    jsonBody["status"]  = "ok";
    jsonBody["message"] = "Position received";

    Json::Value mehConfig;

    // возможно ли перемещение
    try
    {
        mehConfig = sutils::getConfigMehJsonValues();
        movementSutils::canMove(x,y, mehConfig);
    }

    catch(const std::exception& e)
    {       
        if(std::string(e.what()) == "The position is wrong"){

            jsonBody["status"]  = "error";
            jsonBody["message"] = "The position is wrong";

            sutils::rewriteConfigMehJsonFile(mehConfig);

        }
        else{

            jsonBody["message"] = e.what();
        }

        auto response = drogon::HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

        callback(response);
        return;;
    }

    // перемещение
    try
    {
        movementSutils::moving(x, y, mehConfig);

        sutils::rewriteConfigMehJsonFile(mehConfig);

        jsonBody["status"]  = "ok";
        jsonBody["message"] = "The position was changed";
        auto response = drogon::HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(drogon::HttpStatusCode::k201Created);
        

        callback(response);
        return;
    }
    catch(const std::exception& e)
    {
        jsonBody["status"]  = "error";
        jsonBody["message"] = e.what();

        auto response = drogon::HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);

        callback(response);
        return;
    }   
}

void MovementController :: postTurn(const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback){

    Json::Value jsonBody;

    auto requestBody = req->getJsonObject();

    // Проверка что пришло направление меха
    if (!requestBody || !requestBody->isMember("faced_to")) {

        jsonBody["status"] = "error";
        jsonBody["message"] = "The turn is required";
        auto response = HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(HttpStatusCode::k400BadRequest);
        callback(response);
        return;
    }

    std::string turn  = requestBody->get("faced_to", "").asString();
    std::cout << turn << std::endl;

    Json::Value mehConfig;

    // возможен ли поворот
    try
    {
        mehConfig = sutils::getConfigMehJsonValues();
        movementSutils::canTurn(turn, mehConfig);
    }

    catch(const std::exception& e)
    {       
        if(std::string(e.what()) == "The turn is wrong"){

            jsonBody["status"]  = "error";
            jsonBody["message"] = "The turn is wrong";

            sutils::rewriteConfigMehJsonFile(mehConfig);

        }
        else{

            jsonBody["status"] = e.what();
        }

        auto response = drogon::HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

        callback(response);
        return;;
    }

    try
    {
        movementSutils::turning(turn, mehConfig);

        sutils::rewriteConfigMehJsonFile(mehConfig);

        jsonBody["status"]  = "ok";
        jsonBody["message"] = "Robot turned";
        auto response = drogon::HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(drogon::HttpStatusCode::k201Created);

        callback(response);
        return;
    }
    catch(const std::exception& e)
    {
        if(std::string(e.what()) == "The turn is wrong"){

            jsonBody["status"]  = "error";
            jsonBody["message"] = "The turn is wrong";

            sutils::rewriteConfigMehJsonFile(mehConfig);

        }
        else{

            jsonBody["message"] = e.what();
        }

        auto response = drogon::HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

        callback(response);
        return;;
    }
    

}




