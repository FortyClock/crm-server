#include <drogon/drogon.h>
#include "controllers/StateController.h"
#include "controllers/MapController.h"
#include "controllers/MovementController.h"
#include "controllers/ActionController.h"



int main() {

    drogon::app()
        .loadConfigFile(std::string(getenv("CRM_SERVER_CONFIG_DIR")))
        .run();

    return 0;
}
