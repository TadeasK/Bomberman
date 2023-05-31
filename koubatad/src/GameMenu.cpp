#include "GameMenu.hpp"

GameMenu::GameMenu(bool test)
        : Menu()
{
    m_Test = test;
    m_Name = "Select game mode";

    menuItems = {
            "Single Player",
            "Multiplayer",
            "Back"
    };
}

//----------------------------------------------------------------------------------------------

void GameMenu::takeAction(int currSelect)
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

void GameMenu::startSingle() const
{
    std::string name = "Choose level";
    LevelMenu game(name, m_Test);
    game.runMenu();
}

//----------------------------------------------------------------------------------------------

void GameMenu::startMulti() const
{
    std::string name = "Choose map";
    LevelMenu game(name, m_Test, true);
    game.runMenu();
}
