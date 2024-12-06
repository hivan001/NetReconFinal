#include <gtest/gtest.h>
#include "Menu.h"
#include "TcpScan.h"
#include "WriteResults.h"
#include <asio.hpp>
#include <fstream>

class MockTcpIntegratedScan : public TcpScan {
public:
    MockTcpIntegratedScan(asio::io_context& io_context, asio::error_code& error)
        : TcpScan(io_context, error) {
        }

    std::string get_user_input() const override {
        return "127.0.0.1";
    }

};
class MockMenuIntegrated : public Menu{
    public:
    asio::io_context io_context;
    asio::error_code error;
    MockMenuIntegrated(int argc, char* argv[]):Menu(argc,argv){}

    int init(std::string scan_type) override
    {   WriteResults writer;

        if(scan_type == "tcp")
        {
            MockTcpIntegratedScan scanner(io_context, error);

            if(scanner.Scan() == 1)
            {
                std::cout<<"TCP Scan failed"<<std::endl;
                return 1;
            }
            else
            {
                scanner.printResults();
                writer.addScanToResults(scanner.resultsToJSON());
                writer.writeJSONFile("test_results/");
            }
        }
        else if(scan_type == "udp")
        {
            //udp scan
        }
        else if(scan_type == "m60")
        {
            //both tcp and udp
        }


        return 0;


    }
};

class IntegratedTest : public testing::Test {
    public:
        int argc;
        char** argv;
        MockMenuIntegrated menu;

        IntegratedTest() 
            : argc(1), argv(new char*[2]), menu(argc, argv) {
            argv[0] = strdup("-t");
            argv[1] = nullptr;
        }

        ~IntegratedTest() {
            free(argv[0]);
            delete[] argv;
        }
};


TEST_F(IntegratedTest, TestInit){
    menu.run();

        std::string filepath = "test_results/results.json";
        std::ifstream TestResults(filepath);
        std::string test_ip;

        if(TestResults.is_open())
        {
            json test_output;
            TestResults >> test_output;

            test_ip = test_output["IPs"][0]["IP"];

        }
        else
        {
            FAIL();
        }

        TestResults.close();

    ASSERT_EQ(test_ip, "127.0.0.1");
}