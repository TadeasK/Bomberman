#include "LevelMenu.hpp"

LevelMenu::LevelMenu(std::string &name, bool multi,
                     const std::string &bestScorePath,
                     const std::string &mapsPath)
        : Menu()
{
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
            "Level 6",
            "Back"
    };
}

//----------------------------------------------------------------------------------------------

void LevelMenu::takeAction(int currSelect)
{
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
        case MAP6:
            cleanUp();
            m_Map = MAP6 + 1;
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

void LevelMenu::runGame()
{
    maps.append(std::to_string(m_Map));
    try {
        GameManager game(m_Multi, maps, bestScoreFile, m_Test);
        game.runMenu();
    }
    catch (std::string &err) {
        displayErr(err, "Try selecting different map.");
    }
    maps.pop_back();
}

//----------------------------------------------------------------------------------------------