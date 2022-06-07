#pragma once

#include "Menu.hpp"

class OptionsMenu: public Menu
{
public:
    /**
    * @brief Initializes options window, operates based on user input
    *
    */
    OptionsMenu();

private:
    enum OPTIONS { MOVEMENT_UP, MOVEMENT_DOWN, MOVEMENT_LEFT, MOVEMENT_RIGHT, PLACE_BOMB, BACK };

    virtual void takeAction(size_t currSelect) override;
};