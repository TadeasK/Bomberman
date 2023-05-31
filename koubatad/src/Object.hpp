#pragma once

#include "ncurses.h"
#include <utility>

/**
 * @brief A class representing any object in the game 
 * 
 */
class Object
{
public:
    /**
     * @brief Construct a new Object at given position
     * 
     * @param x An X position of object 
     * @param y A Y position of object
     * @param window Window where object is to be displayed
     */
    Object( int x, int y, WINDOW * window );

    virtual ~Object () = default;

    /**
     * @brief Draws object into environment 
     * 
     * @return true If drawn successfully
     * @return false If object doesn't exist anymore
     */
    virtual bool drawObj () const = 0;

    virtual void receiveEffect ( int effect );

    virtual std::pair<int,int> getPosition();

    enum EFFECT {
        DAMAGE, LEVITATE, DETONATOR, BOMB_INC, RADIUS_INC, HEAL,
    };

protected:
    WINDOW * m_Window; // Window where object is displayed
    int m_X; // A current X position of object
    int m_Y; // A current  Y position of object
    bool m_Exist = true; // If object exists or if it has been destroyed/killed

    const int GAME_WINDOW_HEIGHT = 15;
    const int GAME_WINDOW_WIDTH = 15;
};