#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class StateController : public drogon::HttpController<StateController>
{
  public:
    METHOD_LIST_BEGIN
    
    ADD_METHOD_TO(
      StateController::getState,
      "/state",
      drogon::Get
    );

    METHOD_LIST_END


    void getState(const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback);
    
};
