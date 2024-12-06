#include <iostream>
#include <asio.hpp>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "WriteResults.h"
#include <fstream>

WriteResults::WriteResults():scanResults(scanResults){};

void WriteResults::addScanToResults(json results)
{
    scanResults = results;
    //I'll eventually need to find a way to combine tcp and udp results into the main results file
}

void WriteResults::writeJSONFile(std::string path) const
// {   std::string path = "results/";
    {
    std::string filename = "results.json";
    std::string filepath = path + filename;
    std::ofstream Results(filepath);

    try
    {
        if(Results.is_open())
        {
            Results<<scanResults.dump(4);
            std::cout<<"Results written to results.json"<<std::endl;
            Results.close();
        }
        else
        {
            throw std::runtime_error("Failed to open JSON file");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    



}

json WriteResults::getScanResults()
{
    return scanResults;
}