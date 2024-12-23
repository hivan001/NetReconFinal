#include <array>
#include <iostream>
#include <asio.hpp>
#include "TcpScan.h"
#include "WriteResults.h"
#include "Menu.h"

int main(int argc, char* argv[])
{  try
    {
        Menu menu(argc, argv);

        menu.run();

        if(std::system("python3 -m main") == 1)
        {
            throw std::runtime_error("Unable to build GUI");
        }
    }catch(const std::exception& e){
        std::cout<<"There was an error running Net Recon"<<e.what()<<std::endl;
    }

    return 0;

}

