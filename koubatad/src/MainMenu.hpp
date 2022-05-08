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
     * @brief Operates main menu, based on user choice can start the game,
     *  show amd change settings or show help
     * 
     */
    void menuLoop();

private:
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
};

