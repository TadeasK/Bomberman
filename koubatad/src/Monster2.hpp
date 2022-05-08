#pragma once

#include "Enemy.hpp"

/**
 * @brief A class representing any Monster2 object
 * 
 */
class Monster2: public Enemy
{
public:
    /**
     * @brief Construct a new Monster2 object
     * 
     * @param x An X position of new Monster2
     * @param y An Y position of new Monster2
     * @param speed Movement speed of Monster2
     */
    Monster2( int x, int y, int speed);
    ~Monster2 () {};

    virtual bool drawObj() const override;
    
    virtual void move( /*Parameter defining the direction of moving*/ ) override;
};