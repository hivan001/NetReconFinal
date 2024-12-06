#include <gtest/gtest.h>
#include "WriteResults.h"
#include <nlohmann/json.hpp>


/*

------------------Write Results Unit Tests---------------------

Write Results Unit Tests
Initialization of test and mock classes
*/
using json = nlohmann::json;
class WriteResultsTest : public testing::Test {
    protected:
    WriteResults writer;
    WriteResultsTest() : writer(){}
};

/*

-----------------Test: 0 ----------------------

Description: Testing the initialization of the class


*/
TEST_F(WriteResultsTest, TestInit){
    ASSERT_TRUE(writer.getScanResults().empty());
}

/*

-----------------Test: 1 ----------------------

Description: Testing the addScanToResults method


*/

TEST_F(WriteResultsTest, TestAddScanToResults){
    json test;
    test["test"] = "test";

    writer.addScanToResults(test);


    ASSERT_EQ(writer.getScanResults()["test"], "test");
}

