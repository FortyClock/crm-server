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
        err["status"] = "error";
        err["message"] = "Empty data";

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

        mehConfig = sutils::getConfigMehJsonValues();

        actionSUtils::canShooting(x, y, mehConfig);

    }
    catch(const std::exception& e)
    {
        Json::Value err;

        if(std::string(e.what()) == "broke_gun_manip"){

            err["status"] = "error";
            err["message"] = "Gun manipulator broke";

            sutils::rewriteConfigMehJsonFile(mehConfig);

        }
        else{

            err["status"] = "error";
            err["message"] = e.what();
        }

        auto response = drogon::HttpResponse::newHttpJsonResponse(err);
        response->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

        callback(response);
        return;
    }
    

    try
    {
        
        Json::Value resp;
        resp["status"] = "success";
        resp["message"] = actionSUtils::shooting(x, y, mehConfig);

        sutils::rewriteConfigMehJsonFile(mehConfig);

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
        err["status"] = "error";
        err["message"] = e.what();

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
        err["status"] = "error";
        err["message"] = "Empty data";

        auto response = drogon::HttpResponse::newHttpJsonResponse(err);
        response->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

        callback(response);
        return;

    }

    std::string id = reqBody->get("id", "Empty").asString();
    Json::Value mehConfig = {};

    try
    {

        mehConfig = sutils::getConfigMehJsonValues();

        actionSUtils::canRepairing(id, mehConfig["robot_state"]);

    }
    catch(const std::exception& e)
    {

        Json::Value err;
        err["status"] = "error";
        err["message"] = e.what();

        auto response = drogon::HttpResponse::newHttpJsonResponse(err);
        response->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

        callback(response);
        return;

    }


    try
    {
        actionSUtils::repairing(id, mehConfig);

        sutils::rewriteConfigMehJsonFile(mehConfig);

        Json::Value resp;
        resp["status"] = "success";
        resp["message"] = "Successful repair";

        auto response = drogon::HttpResponse::newHttpJsonResponse(resp);
        response->setStatusCode(drogon::HttpStatusCode::k201Created);

        callback(response);
        return;

    }
    catch(const std::exception& e)
    {

        Json::Value err;
        err["status"] = "error";
        err["message"] = e.what();

        auto response = drogon::HttpResponse::newHttpJsonResponse(err);
        response->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);

        callback(response);
        return;

    }
    
}


