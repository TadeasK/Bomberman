#pragma once

#include "Special.hpp"

/**
 * @brief A class representing buff that increases player health
 * 
 */
class BuffHeal : public Special
{
public:
    /**
     * @brief Construct a new BuffHeal object
     * 
     * @param x A X position of the buff
     * @param y An Y position of the buff
     * @param window Window, where object is displayed
     * @param activeTime Time for which Special is active (in frames)
     */
    BuffHeal(int x, int y, WINDOW *window, int activeTime = 70000);

    virtual bool drawObj() const override;

    virtual int giveEffect() override;

private:
    /// Char representing buff on game window
    const char m_Repr = 'H';
};