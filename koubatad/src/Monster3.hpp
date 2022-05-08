#pragma once

#include "Enemy.hpp"

/**
 * @brief A class representing any Monster3 object
 * 
 */
class Monster3: public Enemy
{
public:
    /**
     * @brief Construct a new Monster3 object
     * 
     * @param x An X position of new Monster3
     * @param y An Y position of new Monster3
     * @param speed Movement speed of Monster3
     */
    Monster3( int x, int y, int speed);
    ~Monster3 () {};

    virtual bool drawObj() const override;
    
    virtual void move( /*Parameter defining the direction of moving*/ ) override;
};