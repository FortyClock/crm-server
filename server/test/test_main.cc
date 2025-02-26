#include "gtest/gtest.h"
#include "../sutils/actionSutils.h"
#include "../sutils/sutils.h"
#include "testClass.h"

#include <cstdlib>
#include <jsoncpp/json/json.h>



int main(int argc, char** argv) 
{

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
