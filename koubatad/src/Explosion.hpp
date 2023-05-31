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
     */
    Explosion(int x, int y, WINDOW *window);

    virtual bool drawObj() const override;

    virtual int giveEffect() override;

    virtual int collision() const override;

private:
    const char m_Repr = 'x';
};