// Given a /24 CIDR address or single IP, return a vector of IP objects
//Should be 254 IPs for a /24 network
// Example input is "192.168.100.0/24"

#include <iostream>
#include <asio.hpp>
#include "BaseScan.h"

int BaseScan::checkIp(std::string& input, asio::system_error& ec, std::string& cidr) const 
{   int returnCode = 0;
    std::string address = "";
try{
    //Check to see if CIDR passed in
    if(cidr != "")
    {   int numCidr = 0;
        try
        {
            numCidr = std::stoi(cidr);
        }
        catch(const std::exception& e)
        {   std::cout<<"Invalid CIDR passed in, please try again"<<std::endl;
            std::cerr << e.what() << '\n';

            returnCode = 1;
        }

        if(numCidr > 30 || numCidr < 24)
        {
            throw std::invalid_argument("/" + std::to_string(numCidr) + " network is not supported. Please choose a CIDR from /24 - /30\n");
        }

        address = input;
        address.erase(input.length() - 3);
    }
    else
    {
        address = input;
    }
        //Using the make_address function to check for valid IPs
        asio::ip::address adr = asio::ip::make_address(address);
    }
    catch(const asio::system_error &ec)
    {   
        std::cout<<"Unable to resolve the IP address, please try a different IP or CIDR \n"<<std::endl;
        returnCode = 2;
    }
    catch(const std::invalid_argument &e)
    {
        std::cerr<<e.what()<<std::endl;
        returnCode = 3;
    }

    return returnCode;
    
}

std::string BaseScan::get_user_input() const
{   
    std::string input;
    std::cin.clear();
    std::cout<<"Enter Single IP or IP with CIDR Notation"<<std::endl;
    std::cin>>input;

    return input;
}

std::vector<asio::ip::address> BaseScan::get_Ips() const
{   std::string input;
    asio::system_error ec;
    std::string cidr = "";
    int hosts = 0;
    std::vector<asio::ip::address> Ips;

    input = get_user_input();

    //Checking to see if user passed in a CIDR
    std::size_t cidrSearch = input.find("/");

    if(cidrSearch != std::string::npos)
    {
        cidr = input.substr(input.length() - 2, 2);
    }

    if(checkIp(input, ec, cidr)>0)
    {
        get_Ips();
    }



    //Either single IP or CIDR is good
    if(cidr == "")
    {   
        Ips.reserve(1);
        asio::ip::address adr = asio::ip::make_address(input);

        Ips.push_back(adr);

    }
    else
    {
        auto hostFinder = cidrHosts.find(cidr);
        hosts = hostFinder->second;

        Ips.reserve(hosts);
        std::string firstThreeOctets = "";
        std::string strLastOctet = "";
        int lastOctet = 0;
        int count = 0;
        
        //Removing the CIDR
        input.erase(input.length() - 3,3);


        //Looping through the IP to break apart the first three and last octet
        for(int i = 0; i < input.length(); i++)
        {   
            if(count == 3)
            {
                strLastOctet+=input[i];
            }
            else if(input[i] == '.')
            {
                count++;
                firstThreeOctets+=input[i];
            }
            else
            {   
                firstThreeOctets+=input[i];
            }
            
        }


        lastOctet = std::stoi(strLastOctet);
    
        //Loop to populate the vector of IPs
        for(int i = lastOctet; i < (lastOctet+hosts) && i < 255; i++)
        {   
            asio::ip::address adr = asio::ip::make_address(firstThreeOctets + std::to_string(i));
            Ips.push_back(adr);
        }


    }
    return Ips;

}


