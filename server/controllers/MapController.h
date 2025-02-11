#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class MapController : public drogon::HttpController<MapController>
{
  public:
    METHOD_LIST_BEGIN

    /*
    ADD_METHOD_TO(
      MapController::какая-то-функция,
      "/какой/то/путь",
      drogon::какой-то-метод
    );

    ADD_METHOD_TO();

    и так далее
    */

    METHOD_LIST_END


    /*void какая-то-функция(const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    и так далее

    */
    
};
