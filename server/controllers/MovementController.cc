#include "MovementController.h"
#include "sutils.h"
#include "movementSutils.h"
#include "jsoncpp/json/json.h"
#include <iostream>

void MovementController ::postPosition(const drogon::HttpRequestPtr &req,
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
    //auto response = HttpResponse::newHttpJsonResponse(jsonBody);
    //callback(response);

    Json::Value mehConfig;

    try
    {
        mehConfig = sutils::getConfigMehJsonValues("mehConfig-example.json");
        movementSutils::canMove(x,y, mehConfig);
    }

    catch(const std::exception& e)
    {
        
        if(std::string(e.what()) == "The position is wrong"){


            jsonBody["status"]  = "error";
            jsonBody["message"] = "The position is wrong";

            sutils::rewriteJsonFile("mehConfig-example.json", mehConfig);

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
        //Json::Value resp;
        movementSutils::moving(x, y, mehConfig);

        sutils::rewriteJsonFile("mehConfig-example.json", mehConfig);

        jsonBody["status"]  = "ok";
        jsonBody["message"] = "The position was changed";
        auto response = drogon::HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(drogon::HttpStatusCode::k201Created);
        

        callback(response);
        return;
    }
    catch(const std::exception& e)
    {
        Json::Value err;
        err["error"] = e.what();

        auto response = drogon::HttpResponse::newHttpJsonResponse(err);
        response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);

        callback(response);
        return;
    }
    
}




