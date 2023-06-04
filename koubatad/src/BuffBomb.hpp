#pragma once

#include "Special.hpp"

/**
 * @brief Class representing buff that increases player's max bomb count 
 * 
 */
class BuffBomb : public Special
{
public:
    /**
     * @brief Construct a new Buff Bomb object
     * 
     * @param x A X position of the buff
     * @param y An Y position of the buff
     * @param window Window, where object is displayed
     * @param activeTime Time for which Special is active (in frames)
     */
    BuffBomb(int x, int y, WINDOW *window, int activeTime = 70000);

    virtual bool drawObj() const override;

    virtual int giveEffect() override;

private:
    /// Char representing buff on game window
    const char m_Repr = 'B';
};