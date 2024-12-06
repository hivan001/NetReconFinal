#ifndef WRITERESULTS_H
#define WRITERESULTS_H
#include <iostream>
#include <asio.hpp>
#include <unordered_map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
class WriteResults
{
    public:
        WriteResults();
        void addScanToResults(json results);
        virtual void writeJSONFile(std::string path) const;
        json getScanResults();


    private:
        json scanResults;

};


#endif