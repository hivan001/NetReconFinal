#include <gtest/gtest.h>
#include <asio.hpp>
#include "TcpScan.h"
#include "BaseScan.h"
#include <sstream>


/*

------------------TCP Unit Tests---------------------

TCP Scan and Base Scan Functions Unit Tests
Initialization of test and mock classes
*/

class TcpScanTest : public testing::Test {
    protected:
    asio::io_context io_context;
    asio::error_code error;
    TcpScan tcpscan;
    TcpScanTest() : tcpscan(io_context, error){}
};

class MockTcpScan : public TcpScan {
public:
    MockTcpScan(asio::io_context& io_context, asio::error_code& error)
        : TcpScan(io_context, error) {}

    std::string get_user_input() const override {
        return "127.0.0.1";
    }
    struct ScannedIp {
    std::vector<std::string> ports;
    };
    std::unordered_map<std::string, ScannedIp> results_map;



    
};


/*

-----------------Test: 0 ----------------------

Description: Testing the initialization of the class and results map


*/
TEST_F(TcpScanTest, TestInit){
    ASSERT_TRUE(tcpscan.getResultsMap().empty());
}

/*

-----------------Test: 1 ----------------------

Description: Testing the make tcp endpoints method


*/

TEST_F(TcpScanTest, TestEndpoints){
    std::vector<asio::ip::address> ips;
    std::string ip_str = "127.0.0.1";
    asio::ip::address ip = asio::ip::make_address(ip_str);

    ips.push_back(ip);

    ASSERT_FALSE(tcpscan.make_tcp_endpoints(ips).empty());
}

/*

-----------------Test: 2 ----------------------

Description:Testing the get_Ips method


*/
TEST_F(TcpScanTest, TestGetValidIp){
    MockTcpScan mockScan(io_context, error);
    std::vector<asio::ip::address> ips = mockScan.get_Ips();

    ASSERT_EQ(ips.size(), 1);

}

/*

-----------------Test: 3 ----------------------

Description:Testing valid ip using the checkIp method


*/
TEST_F(TcpScanTest, TestCheckValidIp){
    std::string ip = "127.0.0.1";
    std::string cidr = "";
    asio::system_error test_error;
    int result = tcpscan.checkIp(ip,test_error,cidr);

    ASSERT_EQ(result, 0);

}


/*

-----------------Test: 4 ----------------------

Description:Testing invalid ip using the checkIp method


*/
TEST_F(TcpScanTest, TestCheckInvalidIp){
    std::string ip = "127.0.0.300";
    std::string cidr = "";
    asio::system_error test_error;
    int result = tcpscan.checkIp(ip,test_error,cidr);

    ASSERT_GT(result, 0);

}


/*

-----------------Test: 5 ----------------------

Description:Testing valid cidr using the checkIp method


*/
TEST_F(TcpScanTest, TestCheckValidCidr){
    std::string ip = "10.0.0.1/24";
    std::string cidr = "24";
    asio::system_error test_error;
    int result = tcpscan.checkIp(ip,test_error,cidr);

    ASSERT_EQ(result, 0);

}


/*

-----------------Test: 6 ----------------------

Description:Testing invalid cidr using the checkIp method


*/
TEST_F(TcpScanTest, TestCheckInvalidCidr){
    std::string ip = "127.0.0.1/18";
    std::string cidr = "18";
    asio::system_error test_error;
    int result = tcpscan.checkIp(ip,test_error,cidr);

    ASSERT_GT(result, 0);

}


/*

-----------------Test: 7 ----------------------

Description: testing adding ip to results. This isn't a standalone method but
components are implemented in the scan class


*/
TEST_F(TcpScanTest, TestAddToResults){
    std::string ip = "127.0.0.1";
    std::vector<std::string> ips;
    std::string port = "80";
    ips.push_back(port);
    
    MockTcpScan mockscan(io_context, error);
    MockTcpScan::ScannedIp ip_data;
    ip_data.ports.push_back(port);
    std::string ip_result = "";
    std::string ip_port = "";

    mockscan.results_map[ip] = ip_data;

    auto it = mockscan.results_map.find(ip);

    if(it != mockscan.results_map.end())
    {
        ip_result = it->first;
    }


    ASSERT_EQ(ip_result, "127.0.0.1");

    ip_port = mockscan.results_map[ip_result].ports[0];
    ASSERT_EQ(ip_port, "80");

}

