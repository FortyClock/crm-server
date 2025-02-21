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

    // Поворт на 90 градусов
    ADD_METHOD_TO(
      MovementController::postTurn,
      "/turn",
      drogon::Post
    );
        
    METHOD_LIST_END
    
    
    void postPosition(const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    void postTurn(const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback);
};
