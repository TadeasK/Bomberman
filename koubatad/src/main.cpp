#include "MainMenu.hpp"

int main ()
{
    MainMenu game;
    if ( !game.initNcurses() )
        return 1;
        
    game.menuLoop();

    return 0;
}