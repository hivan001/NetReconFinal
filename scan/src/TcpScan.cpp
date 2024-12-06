
#include <iostream>
#include <asio.hpp>
#include "BaseScan.h"
#include "TcpScan.h"

using asio::ip::tcp;


    TcpScan::TcpScan(asio::io_context& io_context, asio::error_code& error):io_context(io_context), error(error), 
    socket(io_context), resolver(io_context){
        // this->results_map = results_map;
        // this->results = results;
    };

    std::vector<asio::ip::tcp::endpoint> TcpScan::make_tcp_endpoints(std::vector<asio::ip::address> ips)
    {   
        std::vector<asio::ip::tcp::endpoint> endpoints;
        // Going to start by only scanning the 1023 most common ports

        for(asio::ip::address ip : ips)
        {   
            try
            {
                for(int i = 0; i < 1024; i++)
                {   
                    asio::ip::tcp::endpoint endpoint(ip, i);
                    endpoints.push_back(endpoint);
                }
                //---------Manually Adding DB and Testing Port----------//
                std::vector<int> extra_ports = {3306,5432,3389,27017,1521,1433,8080,2000};
                for(auto extra_port : extra_ports)
                {
                    asio::ip::tcp::endpoint endpoint(ip, extra_port);
                    endpoints.push_back(endpoint);
                }

            }
            catch(const asio::system_error &ec)
            {
                std::cout<<"Unable to create endpoints for "+ip.to_string()<<std::endl;
            }

        }

        return endpoints;
    }

    int TcpScan::Scan()
    {   
        this->ips = get_Ips();

        this->endpoints = make_tcp_endpoints(ips);


        try{

            for(const auto& endpoint : endpoints)
            {
                asio::error_code error;

                std::string port = std::to_string(endpoint.port());

                if(socket.is_open())
                {
                    socket.close();
                }

                asio::ip::tcp::resolver::results_type endpointScan = resolver.resolve(endpoint); //can't iterate of endpoints and pass in directly

                asio::connect(socket,endpointScan, error);

                if(error == asio::error::connection_refused)
                {
                    continue;
                }
                else
                {
                    std::cout<<"\033[32m"<<"Connection is open on port: "+port<<std::endl<<std::endl;
                    results_map[endpoint.address().to_string()].ports.push_back(port);

                }

                std::cout<<"\033[0m";
            }         

        }catch (const asio::system_error& e) 
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }

        return 0;
    }

    void TcpScan::printResults()
    {
        for(const auto& result : results_map)
        {   std::cout<<std::endl;
            std::cout<<"\033[0m"<<result.first<<" has "<<result.second.ports.size()<<" port(s) open"<<std::endl<<std::endl;
            std::cout<<"\033[32m"<<"Ports open: \n";
            for(std::string port : result.second.ports)
            {
                std::cout<<"\033[32m"<<port<<std::endl;
            }
        }
        std::cout<<"\033[0m"<<std::endl;
    }

    json TcpScan::resultsToJSON()
    {   int i = 0; // using this to loop through the array
        for(const auto& ip : results_map)
        {   json scan_results;
            results["IPs"].push_back(scan_results);
            results["IPs"][i]["IP"] = ip.first;
            results["IPs"][i]["TCP Ports"] = ip.second.ports;
            i++;
        }

        return results;
    }
    const std::unordered_map<std::string, TcpScan::ScannedIp>& TcpScan::getResultsMap() const
    {
        return results_map;
    }


    