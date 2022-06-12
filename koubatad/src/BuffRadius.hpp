#pragma once

#include "Special.hpp"


/**
 * @brief A class representing buff that increases explosion radius of player placed bombs
 * 
 */
class BuffRadius: public Special
{
public:
    /**
     * @brief Construct a new Buff Radius object
     * 
     * @param x A X position of the buff
     * @param y An Y position of the buff
     */
    BuffRadius(int x, int y);

    virtual void drawObj() const override;
    virtual void giveEffect() override;
};