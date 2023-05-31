#pragma once

#include "Menu.hpp"

/**
 * @brief Represents menu which shows available controls
 */
class OptionsMenu : public Menu
{
public:
    /**
    * @brief Initializes options window, operates based on user input
    *
    */
    OptionsMenu();


private:
    enum OPTIONS
    {
        BACK
    };
    /// Settings for player1
    const std::vector<std::string> m_SettingKeysP1 = {
            "PLAYER 1:",
            "",
            "UP    = W",
            "DOWN  = S",
            "LEFT  = A",
            "RIGHT = D",
            "BOMB  = SPACE"
    };

    /// Settings for player2
    const std::vector<std::string> m_SettingKeysP2 = {
            "PLAYER 2:",
            "",
            "UP    = ARR UP",
            "DOWN  = ARR DOWN",
            "LEFT  = ARR LEFT",
            "RIGHT = ARR RIGHT",
            "BOMB  = NUM ENTER"
    };

    /**
     * @brief Display settings for both players
     *
     */
    virtual void displayCustom() override;

    virtual void takeAction(int currSelect) override;
};