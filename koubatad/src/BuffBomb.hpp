#pragma once

#include "Special.hpp"

/**
 * @brief Class representing buff that increases player's max bomb count 
 * 
 */
class BuffBomb: public Special
{
public:
    /**
     * @brief Construct a new Buff Bomb object
     * 
     * @param x A X position of the buff
     * @param y An Y position of the buff
     */
    BuffBomb(int x, int y, WINDOW* window);

    virtual void drawObj() const override;
    virtual void giveEffect() override;
};