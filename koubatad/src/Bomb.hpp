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
    Bomb( int x, int y,WINDOW* window, int timer = 5, int radius = 1);
   
    virtual void drawObj() const override;
  
    /**
     * @brief Counts down timer, at 0 explodes 
     * 
     */
    void countDown();
  
    /**
     * @brief Draws explosion in radius, destroys destroyable objects 
     * 
     */
    void explode();

private:
    int m_Timer; // Current time until explosion
    int m_Radius; // Radius of explosion
};
