#include "LevelMenu.hpp"

LevelMenu::LevelMenu( std::string& name, bool multi,
                                     const std::string& bestScorePath,
                                     const std::string& mapsPath )
    :Menu()
{
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

void LevelMenu::takeAction(size_t currSelect)
{
    switch (currSelect) {
        case MAP1:
            cleanUp();
            m_Map = MAP1+1;
            break;
        case MAP2:
            cleanUp();
            m_Map = MAP2+1;
            break;
        case MAP3:
            cleanUp();
            m_Map = MAP3+1;
            break;
        case MAP4:
            cleanUp();
            m_Map = MAP4+1;
            break;
        case MAP5:
            cleanUp();
            m_Map = MAP5+1;
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
        GameManager game;
        game.runMenu();
}

//----------------------------------------------------------------------------------------------
/*
void LevelMenu::gameLoop()
{
    while ( true ) {
        box(stdscr,0,0);
        for (auto obj: m_Objects) {
            obj->drawObj();
        }
        refresh();
    }
}

//----------------------------------------------------------------------------------------------

void LevelMenu::spawnObjects()
{
    auto player = std::make_shared<Player>(2,2);
    m_Objects.emplace_back(player);
    m_Entities.emplace_back(player);
}

//----------------------------------------------------------------------------------------------

void LevelMenu::prepareMap()
{
    maps.append(std::to_string(m_Map));

    try {
        readConfig(maps);
    }
    catch ( std::string& err ) {
        displayErr( err, "Try selecting different map.");
    }
    maps.pop_back();
}

//----------------------------------------------------------------------------------------------

void LevelMenu::readConfig( const std::string& path) {
    std::fstream inFile(path, inFile.in | inFile.out);
    if (!inFile.is_open() || !inFile.good())
        throw "Couldn't open file: " + path;

    parseFile(inFile);


//    inFile.close();
//    if ( inFile.fail() )
//        throw "Failed closing file: " + path;

}

//----------------------------------------------------------------------------------------------

void LevelMenu::parseFile( std::fstream& file)
{
    std::string line;
    while ( std::getline(file, line) ) {
        std::istringstream parLine(line);
        std::string key;
        if (std::getline(parLine, key, '=')) {
            std::string value;
            if (std::getline(parLine, value))
                storeSetting(key, value);
        }
    }
}

void LevelMenu::storeSetting(std::string &key, std::string &value) {}
*/