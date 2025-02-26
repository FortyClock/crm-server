#include "sutils.h"

#include <iostream>
#include <fstream>

#include <jsoncpp/json/json.h>

namespace sutils{

    Json::Value getConfigMehJsonValues(const std::string& filename){
    
        Json::Value allData;
    
        std::ifstream configMehFile(
            std::string(getenv("CRM_SERVER_DB_DIR")) + filename,
            std::ifstream::binary);
        if(!configMehFile.is_open()){
    
            throw std::runtime_error("Can't open the file");
        }
    
        configMehFile >> allData;
    
        configMehFile.close();
        
        if(allData.empty()){
            throw std::runtime_error("File is empty");
        }
    
        return allData;
    
    }

    void rewriteConfigMehJsonFile(const std::string& filename, const Json::Value& allData) {
        
        std::ofstream newMehConfigFile(
            std::string(getenv("CRM_SERVER_DB_DIR")) + filename);
        if(newMehConfigFile.is_open()){
    
            newMehConfigFile << allData;
            newMehConfigFile.close();
        }
        else{
    
            throw std::runtime_error("Can't open file for rewriting");
        }
    }

}

