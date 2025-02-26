#include <cstdlib>
#include <jsoncpp/json/json.h>

#include "../sutils/actionSutils.h"
#include "../sutils/sutils.h"


class ActionSutilsTest: public ::testing::Test{

    public:
        Json::Value getTMPMehConfigFile();

    protected:

        void SetUp() override;

        void TearDown() override;
    
};

