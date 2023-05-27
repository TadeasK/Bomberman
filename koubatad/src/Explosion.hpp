#pragma once

#include "Special.hpp"

/**
 * @brief Class representing bomb explosion
 */
class Explosion: public Special {
public:
    /**
     * @brief Construct a new Explosion object
     *
     * @param x A X position of the explosion
     * @param y An Y position of the explosion
     */
    Explosion(int x, int y);

    virtual void drawObj() const override;
    virtual void giveEffect() override;
};