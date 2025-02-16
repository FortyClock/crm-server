#include <drogon/drogon.h>
#include "controllers/StateController.h"
#include "controllers/MapController.h"
#include "controllers/MovementController.h"
#include "controllers/ActionController.h"



int main() {

    drogon::app()
        .loadConfigFile(
            std::string(getenv("HOME")) + "/crm-server/server/config-example.json"
        )
        .run();

    return 0;
}
