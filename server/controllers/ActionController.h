#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ActionController : public drogon::HttpController<ActionController>
{
  public:
    METHOD_LIST_BEGIN
    
    ADD_METHOD_TO(
      ActionController::postPosition,
      "/position",
      drogon::Post
    );

    METHOD_LIST_END


    void postPosition(
      const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback
    );
    
};
