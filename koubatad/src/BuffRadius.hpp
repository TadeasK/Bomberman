#pragma once

#include "Special.hpp"


/**
 * @brief A class representing buff that increases explosion radius of player placed bombs
 * 
 */
class BuffRadius : public Special
{
public:
    /**
     * @brief Construct a new Buff Radius object
     * 
     * @param x A X position of the buff
     * @param y An Y position of the buff
     * @param window Window, where object is displayed
     */
    BuffRadius(int x, int y, WINDOW *window);

    virtual bool drawObj() const override;

    virtual int giveEffect() override;

private:
    const char m_Repr = 'R';
};