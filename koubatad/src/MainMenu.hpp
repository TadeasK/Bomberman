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
    explicit MainMenu(bool test);

private:
    /// If testing mode is running
    bool m_Test;
    enum OPTIONS
    {
        START_GAME, BEST_SCORES, CONTROLS, QUIT
    };


    /**
    *  @brief Prepares the game to run, starts the game
    *
    */
    void runGame() const;

    /**
     * @brief Operates options menu, user can see and edit configuration
    *
    */
    void controls() const;

    /**
     * @brief Shows score of best runs
     */
    void showLeaderboard() const;

    virtual void takeAction(int currSelect) override;

    virtual void displayCustom() override {};
};


