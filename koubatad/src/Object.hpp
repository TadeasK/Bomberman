#pragma once

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

    /**
     * @brief Draws object into environment 
     * 
     * @return true If drawn succesfully
     * @return false 
     */
    bool drawObj ();
private:
    int m_X;
    int m_Y;
};