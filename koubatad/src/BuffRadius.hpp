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

    virtual bool drawObj() const override;
    virtual int giveEffect() override;
};