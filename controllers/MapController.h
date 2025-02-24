#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class MapController : public drogon::HttpController<MapController>
{
  public:
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
      MapController::getMap,
      "/map",
      drogon::Get
    );

    METHOD_LIST_END


    void getMap(const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback);
   
};
