#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class MovementController : public drogon::HttpController<MovementController>
{
  public:
    METHOD_LIST_BEGIN
    
     ADD_METHOD_TO(
      MovementController::getState,
      "/move",
      drogon::Get
    );
    

    METHOD_LIST_END
    
    void getState(const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback);
};
