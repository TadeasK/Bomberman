#pragma once

#include "Special.hpp"

/**
 * @brief Class representing bomb explosion
 */
class Explosion : public Special
{
public:
    /**
     * @brief Construct a new Explosion object
     *
     * @param x A X position of the explosion
     * @param y An Y position of the explosion
     * @param window Window, where object is displayed
     * @param activeTime Time for which Explosion is active (in frames)
     */
    Explosion(int x, int y, WINDOW *window, int activeTime = 2700);

    virtual bool drawObj() const override;

    virtual int giveEffect() override;

    virtual int collision() const override;

private:
    /// Char representing Explosion on game window
    const char m_Repr = 'x';
};