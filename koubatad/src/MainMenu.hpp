#pragma once

#include "Menu.hpp"
#include "OptionsMenu.hpp"
#include "GameMenu.hpp"
#include <vector>
#include <string>

/**
 * @brief Represents Main menu, prints its contents, operates based on user input
 */
class MainMenu: public Menu
{
public:
    /**
     * @brief Initialize ncurses for menus, read and apply from config file
     * 
     */
    MainMenu();

private:
    enum OPTIONS { START_GAME, CONTROLS, QUIT };

    /**
    * @brief Initializes ncurses window, checks if terminal supports all needed functions
    * @throws String error if terminal size is not sufficient or terminal doesn't support color
    *
    */
    void initNcurses();

    /**
     * @brief Set colors to use
     *
     */
    void static initColors();

    /**
    *  @brief Prepares the game to run, starts the game
    *
    */
    void runGame();

    /**
     * @brief Operates options menu, user can see and edit configuration
    *
    */
    void options();

    virtual void takeAction(size_t currSelect) override;
};


