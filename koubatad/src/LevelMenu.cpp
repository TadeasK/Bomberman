#include "LevelMenu.hpp"

LevelMenu::LevelMenu(std::string &name, bool multi,
                     const std::string &bestScorePath,
                     const std::string &mapsPath)
        : Menu() {
    maps = mapsPath;
    running = true;
    m_Name = name;
    m_Multi = multi;
    bestScoreFile = bestScorePath;

    menuItems = {
            "Level 1",
            "Level 2",
            "Level 3",
            "Level 4",
            "Level 5",
            "Back"
    };
}

//----------------------------------------------------------------------------------------------

void LevelMenu::takeAction(size_t currSelect) {
    switch (currSelect) {
        case MAP1:
            cleanUp();
            m_Map = MAP1 + 1;
            break;
        case MAP2:
            cleanUp();
            m_Map = MAP2 + 1;
            break;
        case MAP3:
            cleanUp();
            m_Map = MAP3 + 1;
            break;
        case MAP4:
            cleanUp();
            m_Map = MAP4 + 1;
            break;
        case MAP5:
            cleanUp();
            m_Map = MAP5 + 1;
            break;
        case BACK:
            running = false;
            cleanUp();
            return;
        default:
            break;
    }
    runGame();
}

//----------------------------------------------------------------------------------------------

void LevelMenu::runGame() {
    maps.append(std::to_string(m_Map));
    GameManager game(m_Multi, maps);
    game.runMenu();
    maps.pop_back();
}

//----------------------------------------------------------------------------------------------