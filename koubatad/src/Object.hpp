#pragma once

#include "ncurses.h"

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
     * @return false 
     */
    virtual void drawObj () const = 0;

protected:
    WINDOW * m_Window; // Window where object is displayed
    int m_X; // A current X position of object 
    int m_Y; // A current  Y position of object
};