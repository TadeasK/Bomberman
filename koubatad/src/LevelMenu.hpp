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
     * @param test Testing configuration
     * @param multi true if multi player, else single player
     * @param bestScorePath Path to best score file
     * @param mapsPath Path to maps file
     * @param configPath Path to configuration file
     */
    explicit LevelMenu(std::string &name, bool test, bool multi = false,
                       const std::string &bestScorePath = "assets/scores.txt",
                       const std::string &mapsPath = "assets/map",
                       const std::string &configPath = "assets/config.txt");


private:
    /// If multiplayer mode selected
    bool m_Multi;
    /// If testing mode is running
    bool m_Test;
    /// Map ID
    int m_Map = 1;

    enum OPTIONS
    {
        MAP1, MAP2, MAP3, MAP4, MAP5, MAP6, BACK
    };
    std::string bestScoreFile;
    std::string maps;
    std::string configFile;

    virtual void takeAction(int currSelect) override;

    virtual void displayCustom() override {};

    /**
     * @brief Starts the game
     */
    void runGame();

};