#pragma once

#include "Menu.hpp"
#include "GameManager.hpp"
#include <ncurses.h>
#include <vector>
#include <memory>
#include <iostream>

/**
 * @brief Operates the game
 */
class LevelMenu : public Menu
{
public:
    /**
     * @brief Constructs LevelMenu
     * @param name Name of menu
     * @param multi true if multi player, else single player
     * @param bestScorePath Path to best score file
     * @param mapsPath Path to maps file
     */
    explicit LevelMenu(std::string &name, bool test, bool multi = false,
                       const std::string &bestScorePath = "assets/scores.txt",
                       const std::string &mapsPath = "assets/map");


private:
    bool m_Multi;
    bool m_Test;
    int m_Map = 1;

    enum OPTIONS
    {
        MAP1, MAP2, MAP3, MAP4, MAP5, MAP6, BACK
    };
    std::string bestScoreFile;
    std::string maps;

    void takeAction(int currSelect) override;

    /**
     * @brief Starts the game
     */
    void runGame();

};