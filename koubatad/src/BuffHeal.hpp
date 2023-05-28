#pragma once

#include "Special.hpp"

/**
 * @brief A class representing buff that increases range at which player can place bombs 
 * 
 */
class BuffThrow: public Special
{
public:
    /**
     * @brief Construct a new Buff Throw object
     * 
     * @param x A X position of the buff
     * @param y An Y position of the buff
     */
    BuffThrow(int x, int y);

    virtual bool drawObj() const override;
    virtual int giveEffect() override;
};