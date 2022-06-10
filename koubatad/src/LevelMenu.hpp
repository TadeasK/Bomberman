#pragma once

#include "Menu.hpp"
#include "GameManager.hpp"
#include <ncurses.h>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief Operates the game
 */
class LevelMenu: public Menu
{
public:
    /**
     * @brief Constructs LevelMenu
     * @param name Name of menu
     * @param multi true if multi player, else single player
     * @param bestScorePath Path to best score file
     * @param mapsPath Path to maps file
     */
    explicit LevelMenu(std::string& name, bool multi = false,
                       const std::string& bestScorePath = "assets/scores.txt",
                       const std::string& mapsPath = "assets/map" );



private:
    bool m_Multi;
    int m_Map = 1;

    enum OPTIONS { MAP1, MAP2, MAP3, MAP4, MAP5, BACK };
    std::string bestScoreFile;
    std::string maps;

    virtual void takeAction( size_t currSelect ) override;

    /**
     * @brief Starts the game
     */
    void runGame();

};