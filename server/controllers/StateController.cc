#include "StateController.h"
#include "jsoncpp/json/json.h"
#include <iostream>

//check
//hello

void StateController::getState(const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback){

    try
    {
        // need to get full robot state
        // for example -> make json answer message = "State controller is working!!!"

        Json::Value resp;      // response from server to crm
        resp["message"] = "State controller is working!!!";

        auto response = drogon::HttpResponse::newHttpJsonResponse(resp);
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

    try
    {
        auto requestBody = req->getJsonObject();

        // check the body is not null
        if (requestBody == nullptr) {
            jsonBody["status"] = "error";
            jsonBody["message"] = "Body is required";
            auto response = HttpResponse::newHttpJsonResponse(jsonBody);
            response->setStatusCode(HttpStatusCode::k400BadRequest);
            callback(response);
            return;
        }

        // check the body contains the message field
        if (!requestBody->isMember("message")) {
            jsonBody["status"] = "error";
            jsonBody["message"] = "Field `message` is required";
            auto response = HttpResponse::newHttpJsonResponse(jsonBody);
            response->setStatusCode(HttpStatusCode::k400BadRequest);
            callback(response);
            return;
        }

        // get the message
        std::string message = requestBody->get("message", "").asString();

        
        std::cout << "Received message: " << message << std::endl;

        jsonBody["status"] = "ok";
        jsonBody["message"] = "Message received: " + message;
        auto response = HttpResponse::newHttpJsonResponse(jsonBody);
        callback(response);

    catch (const std::exception& e)
    {
        jsonBody["status"] = "error";
        jsonBody["message"] = std::string("Error: ") + e.what();
        auto response = HttpResponse::newHttpJsonResponse(jsonBody);
        response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
        callback(response);
    }

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

