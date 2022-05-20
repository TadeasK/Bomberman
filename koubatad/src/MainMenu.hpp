#pragma once

#include "GameLoop.hpp"

/**
 * @brief Represents and operates MainMenu functions 
 * 
 */
class MainMenu
{
public:
    MainMenu();
    ~MainMenu();

    /**
     * @brief Initializes ncurses window, checks if terminal supports all neded functions
     * 
     * @return true If everything went alright
     * @return false If terminal doesn't support colors or doesn't fit minimal size
    */
    bool initNcurses();

    /**
     * @brief Operates main menu, based on user choice can start the game,
     *  show amd change settings or show help
     * 
     */
    void menuLoop();

private:
    int m_WIDTH;
    int m_HEIGHT;
    const static int MIN_WIDTH = 80;
    const static int MIN_HEIGHT = 24;

    /**
     * @brief Operates options menu, user can see and edit configuration 
     * 
     */
    void optionsLoop();
    
    /**
     * @brief Shows help for the game 
     * 
     */
    void helpLoop();
    
    /**
     * @brief Reads user input
     * 
     */
    void readInput();

    /**
     * @brief Set colors to use 
     * 
     */
    void initColors();
};

