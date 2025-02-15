#include "MovementController.h"
#include "jsoncpp/json/json.h"
#include <iostream>

//check
//hello

void MovementController ::postPosition(const drogon::HttpRequestPtr &req,
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

        // Проверка что пришла позиция меха
        if (!requestBody->isMember("x") || !requestBody->isMember("y")) {
            jsonBody["status"] = "error";
            jsonBody["message"] = "Fields 'x' and 'y' are required";
            auto response = HttpResponse::newHttpJsonResponse(jsonBody);
            response->setStatusCode(HttpStatusCode::k400BadRequest);
            callback(response);
            return;
        }

        // Получение позиции
        std::string x = requestBody->get("x", "").asString();
        std::string y = requestBody->get("y", "").asString();
        
        std::cout << "Received position " << x << ", " << y << std::endl;

        jsonBody["status"] = "ok";
        jsonBody["message"] = "Position received";
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




