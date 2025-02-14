#include "ActionController.h"
#include <jsoncpp/json/json.h>

#include <iostream>
#include <fstream>


// ПЕРЕНЕСТИ В SUTILS
Json::Value getConfigMehJsonValues(){

    Json::Value allData;

    std::ifstream configMehFile("../database/mehConfig-example.json", std::ifstream::binary);
    if(!configMehFile.is_open()){

        allData["error"] = "Can't open config meh file";
        return allData;
    }

    configMehFile >> allData;

    configMehFile.close();
    
    if(allData.empty()){
        allData["error"] = "Config file is empty";
        return allData;
    }

    return allData;

}


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

    try
    {
        x = (*reqBody)['x'].asInt();
        y = (*reqBody)['y'].asInt();
    }
    catch(const std::exception& e)
    {
        Json::Value err;
        err["error"] = "Empty data";

        auto response = drogon::HttpResponse::newHttpJsonResponse(err);
        response->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

        callback(response);
    }
    

    // Нужно получить данные о положении робота и его взгляда, а затем сравнить с данными
    // о стрельбе, если они в одном направлении и в 
    // пределах 3х клеток => всё ок, иначе 400 error

    
}


// НЕ СДЕЛАН
void ActionController::repair(const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback){

    
    
}


