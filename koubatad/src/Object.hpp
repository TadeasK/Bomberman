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
     */
    Object( int x, int y);
    virtual ~Object () = default;

    /**
     * @brief Draws object into environment 
     * 
     * @return true If drawn succesfully
     * @return false 
     */
    virtual bool drawObj () const = 0;

protected:
    int m_X; // A current X position of object 
    int m_Y; // A current  Y position of object
};