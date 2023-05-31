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
    explicit ScoreMenu(const std::string &scorePath);

private:
    /// Current scores
    std::map<int, std::pair<std::string, int>> m_Scores;
    enum OPTIONS
    {
        BACK
    };

    virtual void takeAction(int currSelect) override;

    virtual void displayCustom() override;
};
