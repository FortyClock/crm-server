#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class MovementController : public drogon::HttpController<MovementController>
{
  public:
    METHOD_LIST_BEGIN
    
    // Перемещение по XY
    ADD_METHOD_TO(
      MovementController::postPosition,
      "/position",
      drogon::Post
    );
    
    METHOD_LIST_END
    
    void postPosition(const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback);
};
