#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <asio.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
class Menu
{
private:
    int argc;
    char** argv;
    asio::io_context io_context;
    asio::error_code error;
    // json results;

public:
    Menu(int argc, char* argv[]);
    void run();
    virtual int init(std::string scan_type);
};












#endif