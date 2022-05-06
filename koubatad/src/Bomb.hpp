#pragma once

#include "Object.hpp"

/**
 * @brief A class representing Bomb object
 * 
 */
class Bomb: public Object
{
public:
    /**
     * @brief Construct a new Bomb object
     * 
     * @param x An X position of new Bomb
     * @param y An Y position of new Bomb
     * @param timer Time in seconds until explosion
     * @param radius Radius of explosion
     */
    Bomb( int x, int y, int timer, int radius );
private:
    int m_Timer;
    int m_Radius;
};
