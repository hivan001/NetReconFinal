#include "Menu.h"
#include "TcpScan.h"
#include "WriteResults.h"



    Menu::Menu(int argc, char* argv[]){
        this->argc = argc;
        this->argv = argv;
    };

    int Menu::init(std::string scan_type)
    {   WriteResults writer;

        if(scan_type == "tcp")
        {
            TcpScan scanner(io_context, error);

            if(scanner.Scan() == 1)
            {
                std::cout<<"TCP Scan failed"<<std::endl;
                return 1;
            }
            else
            {
                scanner.printResults();
                // results = scanner.resultsToJSON();
                writer.addScanToResults(scanner.resultsToJSON());
                writer.writeJSONFile("results/");
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


        // WriteResults writer;

        // writer.addScanToResults(results);

        // writer.writeJSONFile();

        return 0;


    }

    void Menu::run()
    {
        for(int i = 0; i<argc; i++)
        {   std::string arg = argv[i];

            if(i > 1 && (arg == "-t"|| arg=="-T"))
            {
                init("tcp");
            }
            else if(i > 1 && (arg == "-u"|| arg=="-U"))
            {
                //call udp scan
            }
            else if(i > 1 && (arg == "-m60"|| arg=="-M60"))
            {
                //call tcp and udp scans
            }
            else if(i == 1 && arg.length() > 4)
            {
                init("tcp");//default is TCP
            }
            else if(i == 0)
            {
                init("tcp");
            }
            else
            {
                std::cout<<"Uknown Command Line Arguments Used"<<std::endl;
            }           
        }
    }