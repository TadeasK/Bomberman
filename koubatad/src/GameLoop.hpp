#pragma once


/**
 * @brief Manages the game events 
 * 
 */
class GameLoop
{
public:
    GameLoop();
    ~GameLoop();

    /**
     * @brief Generates map from file
     *
     */
    void generateMap();

    /**
     * @brief Controls the whole game
     *
     */
    void gameControl();
};