#include "MovementController.h"
#include "jsoncpp/json/json.h"
#include <iostream>

//check
//hello

void MovementController :: getState(const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback){

    try
    {
        // need to get full robot state
        //for example -> make json answer message = "State controller is working!!!"

        Json::Value resp;
        resp["message"] = "Movement controller is working!!!";

        auto response = drogon::HttpResponse::newHttpJsonResponse(resp);
        response->setStatusCode(drogon::HttpStatusCode::k200OK);

        callback(response);

        //
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




