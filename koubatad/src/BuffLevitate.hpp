#pragma once

#include "Special.hpp"

/**
 * @brief Class representing Buff that lets player pass through monsters and bombs
 */
class BuffLevitate : public Special
{
public:
    /**
     * @brief Construct a new Levitate Buff object
     *
     * @param x A X position of the buff
     * @param y An Y position of the buff
     * @param window Window, where object is displayed
     */
    BuffLevitate(int x, int y, WINDOW *window);

    virtual bool drawObj() const override;

    virtual int giveEffect() override;

private:
    const char m_Repr = 'L';
};