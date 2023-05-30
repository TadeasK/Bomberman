#pragma once

#include "Menu.hpp"

/**
 * @brief Represents Score menu, prints its contents, operates based on user input
 */
class ScoreMenu : public Menu
{
public:
    /**
     * @brief Initialize ncurses for menus, read and apply from config file
     *
     */
    ScoreMenu();


private:
    enum OPTIONS
    {
        BACK
    };

    void takeAction(int currSelect) override;
};
