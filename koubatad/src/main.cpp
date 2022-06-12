#include "MainMenu.hpp"
#include "LevelMenu.hpp"
#include <iostream>
#include <cstring>
#include <cassert>

void asserts()
{
    // TODO testovani - cteni ze souboru
}

int main ( int argc, char const *argv[] )
{
    if ( argc > 1 && !strcasecmp(argv[1],"-test" ) ) {
        asserts();
    }
    else {
        try {
            MainMenu menu;
            menu.runMenu();
        }
        catch (const std::string &err) {
            std::cout << err << std::endl;
            return 1;
        }
    }
    return 0;

 }