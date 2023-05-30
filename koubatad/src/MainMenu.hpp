#pragma once

#include "Menu.hpp"
#include "OptionsMenu.hpp"
#include "GameMenu.hpp"
#include "ScoreMenu.hpp"
#include <vector>
#include <string>

/**
 * @brief Represents Main menu, prints its contents, operates based on user input
 */
class MainMenu : public Menu
{
public:
    /**
     * @brief Initialize ncurses for menus, read and apply from config file
     * 
     */
    MainMenu(bool test);

private:
    bool m_Test;
    enum OPTIONS
    {
        START_GAME, BEST_SCORES, CONTROLS, QUIT
    };


    /**
    *  @brief Prepares the game to run, starts the game
    *
    */
    void runGame();

    /**
     * @brief Operates options menu, user can see and edit configuration
    *
    */
    void controls();

    /**
     * @brief Shows score of best runs
     */
    void showLeaderboard();

    void takeAction(int currSelect) override;

    void displayCustom() override {};
};


