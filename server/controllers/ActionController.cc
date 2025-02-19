#include "ActionController.h"

#include "actionSutils.h"
#include "sutils.h"
#include <jsoncpp/json/json.h>

#include <iostream>
#include <fstream>

using namespace actionSUtils;
using namespace sutils;


void ActionController::shoot(const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback){

    auto reqBody = (*req).getJsonObject();

    if(!reqBody || !reqBody->isMember("x") || !reqBody->isMember("y")){

        Json::Value err;
        err["error"] = "Empty data";

        auto response = drogon::HttpResponse::newHttpJsonResponse(err);
        response->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

        callback(response);
        return;

    }


    int x = reqBody->get("x", -2).asInt();
    int y = reqBody->get("y", -2).asInt();
    Json::Value mehConfig = {};

    try
    {

        mehConfig = sutils::getConfigMehJsonValues("mehConfig-example.json");

        actionSUtils::canShooting(x, y, mehConfig);

    }
    catch(const std::exception& e)
    {
        Json::Value err;

        if(std::string(e.what()) == "broke_gun_manip"){

            err["error"] = "Gun manipulator broke";

            sutils::rewriteJsonFile("mehConfig-example.json", mehConfig);

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

        sutils::rewriteJsonFile("mehConfig-example.json", mehConfig);

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

    auto reqBody = (*req).getJsonObject();

    if(!reqBody || !reqBody->isMember("id")){

        Json::Value err;
        err["error"] = "Empty data";

        auto response = drogon::HttpResponse::newHttpJsonResponse(err);
        response->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

        callback(response);
        return;

    }

    std::string id = reqBody->get("id", "Empty").asString();
    Json::Value mehConfig = {};

    try
    {

        mehConfig = sutils::getConfigMehJsonValues("mehConfig-example.json");

        actionSUtils::canRepairing(id, mehConfig["robot_state"]);

    }
    catch(const std::exception& e)
    {

        Json::Value err;
        err["error"] = e.what();

        auto response = drogon::HttpResponse::newHttpJsonResponse(err);
        response->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

        callback(response);
        return;

    }


    try
    {
        actionSUtils::repairing(id, mehConfig);

        sutils::rewriteJsonFile("mehConfig-example.json", mehConfig);

        Json::Value resp;
        resp["message"] = "Successful repair";

        auto response = drogon::HttpResponse::newHttpJsonResponse(resp);
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


