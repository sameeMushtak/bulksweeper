#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <regex>

int main()
{
    std::string cmd_list;
    getline(std::cin, cmd_list);
    std::stringstream cmdstream(cmd_list);
    // Need to make sure no command is excessively long
    char cmd_arr[30];
    int x, y;
    std::string cmd;
    while (cmdstream >> cmd) {
        if (cmd.size() + 3 > 30) {
            std::cout << "Too long" << std::endl;
            continue;
        }
        if (std::regex_match(cmd,std::regex("C[0-9]+,[0-9]+"))) {
            strcpy(cmd_arr, cmd.c_str());
            sscanf(cmd_arr, "C%d,%d", &x, &y);
            std::cout << "Clearing " << x << "," << y << std::endl;
        }
        else if (std::regex_match(cmd,std::regex("F[0-9]+,[0-9]+"))) {
            strcpy(cmd_arr, cmd.c_str());
            sscanf(cmd_arr, "F%d,%d", &x, &y);
            std::cout << "Flagging " << x << "," << y << std::endl;
        }
        else if (std::regex_match(cmd,std::regex("X[0-9]+,[0-9]+"))) {
            strcpy(cmd_arr, cmd.c_str());
            sscanf(cmd_arr, "X%d,%d", &x, &y);
            std::cout << "Chording " << x << "," << y << std::endl;
        }
        else {
            std::cout << "Not recognized command" << std::endl;
        }
    }
}
