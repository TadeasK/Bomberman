#pragma once

#include "Menu.hpp"
#include "LevelMenu.hpp"

/**
 * @brief Represents Menu where you can select what game mode to play, starts that game mode
 * 
 */
class GameMenu : public Menu
{
public:
    /**
     * @brief Initializes ncurses window for this menu
     */
    GameMenu(bool test);

private:
    bool m_Test;
    enum OPTIONS
    {
        SINGLE, MULTI, BACK
    };

    /**
     * @brief Starts single player game
     */
     void startSingle();

    /**
     * @brief Starts multi player game
     */
    void startMulti();

    void takeAction(int currSelect) override;
    void displayCustom() override {};

};