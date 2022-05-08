#pragma once

#include "Special.hpp"

/**
 * @brief A class representing buff that allows player to move faster
 * 
 */
class BuffMove: public Special
{
public:
    /**
     * @brief Construct a new Buff Move object
     * 
     * @param x A X position of the buff
     * @param y An Y position of the buff
     */
    BuffMove(int x, int y);
    ~BuffMove() {};

    virtual bool drawObj() const override;
    virtual void giveEffect() override;

};