#pragma once

#include "Special.hpp"

/**
 * @brief A class representing buff that allows player to detonate bomb remotely
 * 
 */
class BuffDetonator : public Special
{
public:
    /**
     * @brief Construct a new Buff Detonator object
     *
     * @param x A X position of the buff
     * @param y An Y position of the buff
     * @param window Window, where object is displayed
     */
    BuffDetonator(int x, int y, WINDOW *window);

    virtual bool drawObj() const override;

    virtual int giveEffect() override;

private:
    const char m_Repr = 'D';
};