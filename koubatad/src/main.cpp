#include "MainMenu.hpp"
#include <iostream>

int main ()
{
    try {
        MainMenu menu;
        menu.runMenu();
    }
    catch (const std::string& err ) {
        std::cout << err << std::endl;
        return 1;
    }
    return 0;
}