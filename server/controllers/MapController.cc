#include "MapController.h"
#include "sutils.h"


void MapController::getMap(const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback){
    
    Json::Value mehConfig = sutils::getConfigMehJsonValues();
    
    if(!mehConfig.isMember("map")){
        Json::Value errorResponse;
        errorResponse["status"] = "error";
        errorResponse["message"] = "map not found in configuration";

        auto response = drogon::HttpResponse::newHttpJsonResponse(errorResponse);
        response->setStatusCode(drogon::HttpStatusCode::k404NotFound);
        callback(response);
        return;
    }

    try
    {
        Json::Value map = mehConfig["map"];

        Json::Value resp;
        resp["status"] = "success";
        resp["data"] = map;

        auto response = drogon::HttpResponse::newHttpJsonResponse(resp);
        response->setStatusCode(drogon::HttpStatusCode::k200OK);

        callback(response);
        return;

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
    

}
