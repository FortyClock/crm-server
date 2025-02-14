#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ActionController : public drogon::HttpController<ActionController>
{
  public:
    METHOD_LIST_BEGIN
    
    ADD_METHOD_TO(
      ActionController::shoot,
      "/shoot",
      drogon::Post
    );

    ADD_METHOD_TO(
      ActionController::repair,
      "/repair",
      drogon::Post
    );

    METHOD_LIST_END


    void shoot(
      const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    void repair(
      const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback);
    
};
