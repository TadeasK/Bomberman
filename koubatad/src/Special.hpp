#pragma once

#include "Object.hpp"

/**
 * @brief A class representing any Special object
 *
 */
class Special : public Object
{
public:
    /**
     * @brief Construct a new Special object
     *
     * @param x An X position of new Bomb
     * @param y An Y position of new Bomb
     * @param window Window, where object is displayed
     * @param lifeSpan Lifespan of object (in frames)
     */
    Special(int x, int y, WINDOW *window, int lifeSpan);

    /**
     * @brief Updates Special effect
     * @return Status of effect
     */
    virtual int update();

    /**
     * @brief If Special object is picked up gives the Player picking it it's bonus 
     * 
     */
    virtual int giveEffect() = 0;

    /**
     * @brief Check if something is on my position
     * @return -1 if my position would be out of map bounds
     * @return 1 if I collide with another object
     * @return 0 if my position is clear
     */
    virtual int collision() const;

protected:
    /// Lifespan in frames
    int m_LifeSpan;
    /// Attributes of effect (for ncurses)
    unsigned int m_Attr = A_NORMAL;

    /**
     * @brief Decreases lifeSpan frames remaining
     */
    void reduceLifeSpan();
};