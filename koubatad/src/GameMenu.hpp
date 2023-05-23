#pragma once

#include "Menu.hpp"
#include "LevelMenu.hpp"

/**
 * @brief Represents Menu where you can select what game mode to play, starts that game mode
 * 
 */
class GameMenu: public Menu
{
public:
    /**
     * @brief Initializes ncurses window for this menu
     */
    GameMenu();

private:
    enum OPTIONS { SINGLE, MULTI, BACK};

    /**
     * @brief Starts single player game
     */
    static void startSingle();

    /**
     * @brief Starts multi player game
     */
    static void startMulti();

    void takeAction(size_t currSelect) override;

};