#include "GameMenu.hpp"

GameMenu::GameMenu()
    :Menu()
{
    running = true;
    m_Name = "Select game mode";

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
    std::string name = "Choose level";
    LevelMenu game(name);
    game.runMenu();
}

//----------------------------------------------------------------------------------------------

void GameMenu::startMulti()
{
    std::string name = "Choose map";
    LevelMenu game(name, true);
    game.runMenu();
}
