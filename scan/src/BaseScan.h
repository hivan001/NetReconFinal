#ifndef BASESCAN_H
#define BASESCAN_H
#include <iostream>
#include <asio.hpp>
#include <unordered_map>

class BaseScan 
{
    public:
        virtual ~BaseScan() = default; //virtual destructor
        virtual int Scan() = 0; // Implemented by concrete factories
        int checkIp(std::string& input, asio::system_error& ec, std::string& cidr) const;
        std::vector<asio::ip::address> get_Ips() const;
        virtual std::string get_user_input() const;

    private:
        std::unordered_map<std::string, int> cidrHosts = {
        {"24", 254},
        {"25", 126},
        {"26", 62},
        {"27", 30},
        {"28", 14},
        {"29", 6},
        {"30", 2}
        };

};


#endif