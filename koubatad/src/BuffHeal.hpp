#pragma once

#include "Special.hpp"

/**
 * @brief A class representing buff that increases player health
 * 
 */
class BuffHeal: public Special
{
public:
    /**
     * @brief Construct a new BuffHeal object
     * 
     * @param x A X position of the buff
     * @param y An Y position of the buff
     */
    BuffHeal(int x, int y,WINDOW* window);

    virtual bool drawObj() const override;
    virtual int giveEffect() override;
};