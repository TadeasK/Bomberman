#pragma once

#include "Enemy.hpp"

/**
 * @brief A class representing any Monster1 object
 * 
 */
class Monster1: public Enemy
{
public:
    /**
     * @brief Construct a new Monster1 object
     * 
     * @param x An X position of new Monster1
     * @param y An Y position of new Monster1
     * @param speed Movement speed of Monster1
     */
    Monster1( int x, int y, int speed);
    ~Monster1 () {};

    virtual bool drawObj() const override;
    
    virtual void move( /*Parameter defining the direction of moving*/ ) override;
};