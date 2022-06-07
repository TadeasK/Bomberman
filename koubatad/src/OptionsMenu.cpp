#include "OptionsMenu.hpp"

OptionsMenu::OptionsMenu()
    : Menu()
{
    getmaxyx(stdscr, m_HEIGHT, m_WIDTH); // Read window parameters
    running = true;
    menuHeight = m_HEIGHT/2;
    menuWidth = m_WIDTH/2;
    menuWindow = newwin(menuHeight, menuWidth, m_HEIGHT/4, m_WIDTH/4 );

    keypad(menuWindow, true);

    menuItems = {
            "UP key = ",
            "DOWN key = ",
            "LEFT key = ",
            "RIGHT key = ",
            "PLACE BOMB key = ",
            "Back"
    };
}

void OptionsMenu::takeAction(size_t currSelect)
{
    switch (currSelect) {
        case MOVEMENT_UP:
            break;
        case MOVEMENT_DOWN:
            break;
        case MOVEMENT_LEFT:
            break;
        case MOVEMENT_RIGHT:
            break;
        case PLACE_BOMB:
            break;
        case BACK:
            running = false;
            cleanUp();
            break;
    }
}