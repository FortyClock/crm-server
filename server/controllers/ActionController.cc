#include "ActionController.h"

#include "actionSutils.h"
#include <jsoncpp/json/json.h>

#include <iostream>
#include <fstream>

using namespace actionSUtils;

// НЕ ЗАВЕРШЁН
void ActionController::shoot(const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback){

    auto reqBody = (*req).getJsonObject();

    if(!reqBody){

        Json::Value err;
        err["error"] = "Empty data";

        auto response = drogon::HttpResponse::newHttpJsonResponse(err);
        response->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

        callback(response);
        return;

    }


    int x = -1, y = -1;
    Json::Value mehConfig = {};

    try
    {

        x = reqBody->get("x", -2).asInt();
        y = reqBody->get("y", -2).asInt();


        mehConfig = actionSUtils::getConfigMehJsonValues("mehConfig-example.json");

        actionSUtils::canShooting(x, y, mehConfig);

    }
    catch(const std::exception& e)
    {
        Json::Value err;

        if(x < 0 || y < 0){

            err["error"] = "Empty data";
        }
        else if(std::string(e.what()) == "broke_gun_manip"){

            err["error"] = "Gun manipulator broke";

            mehConfig["robot_state"]["gun_manip"] = "Empty";
            actionSUtils::rewriteJsonFile("mehConfig-example.json", mehConfig);

        }
        else{

            err["error"] = e.what();
        }

        auto response = drogon::HttpResponse::newHttpJsonResponse(err);
        response->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

        callback(response);
        return;
    }
    

    try
    {
        
        Json::Value resp;
        resp["message"] = actionSUtils::shooting(x, y, mehConfig);

        actionSUtils::rewriteJsonFile("mehConfig-example.json", mehConfig);

        auto response = drogon::HttpResponse::newHttpJsonResponse(resp);
        if(resp["message"] == "Shot"){
            response->setStatusCode(drogon::HttpStatusCode::k200OK);
        }
        else{
            response->setStatusCode(drogon::HttpStatusCode::k201Created);
        }

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


// НЕ СДЕЛАН
void ActionController::repair(const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback){

    
    
}


