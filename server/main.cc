#include <drogon/drogon.h>
#include "controllers/StateController.h"
#include "controllers/MapController.h"
#include "controllers/MovementController.h"
#include "controllers/ActionController.h"

#include <cstdlib>



int main(int argc, char* argv[]) {

    if(argc != 3){
        
        std::cout << "error\n   What(): invalid command args\n"
        << "   Correct args: cmd command [/path/to/server/binary/file "
        << "/path/to/server/config/file /path/to/meh/config/file]" << "\n";
        return 1;
    }

    std::string serverCfgPath = argv[1];


    std::string mehCfgPath = argv[2];
    setenv("CRM_SERVER_DB_DIR", mehCfgPath.c_str(), 1);

    drogon::app()
        .loadConfigFile(serverCfgPath)
        .run();

    return 0;
}
