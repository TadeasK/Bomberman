#pragma once

#include "Menu.hpp"

/**
 * @brief Manages the game events 
 * 
 */
class GameMenu: public Menu
{
public:
    GameMenu();

private:
    enum OPTIONS { SINGLE, MULTI, BACK};

    /**
     * @brief Starts single player game
     */
    void startSingle();

    /**
     * @brief Starts multi player game
     */
    void startMulti();

    virtual void takeAction(size_t currSelect) override;

};