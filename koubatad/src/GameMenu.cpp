#include "GameMenu.hpp"

GameMenu::GameMenu()
{
    running = true;
    getmaxyx(stdscr,m_WIDTH,m_HEIGHT);
    m_Name = "Select game mode";
    menuHeight = m_HEIGHT / 2;
    menuWidth = m_WIDTH / 2;
    menuWindow = newwin(menuHeight, menuWidth, m_HEIGHT / 4, m_WIDTH / 4);
    keypad(menuWindow, true);

    menuItems = {
            "Single Player",
            "Multiplayer",
            "Back"
    };
}

//----------------------------------------------------------------------------------------------

void GameMenu::takeAction(size_t currSelect)
{
    switch (currSelect) {
        case SINGLE:
            cleanUp();
            startSingle();
            break;
        case MULTI:
            cleanUp();
            startMulti();
            break;
        case BACK:
            running = false;
            cleanUp();
            break;
        default:
            break;
    }
}

//----------------------------------------------------------------------------------------------

void GameMenu::startSingle()
{

}

//----------------------------------------------------------------------------------------------

void GameMenu::startMulti()
{

}
