#pragma once

#include "Object.hpp"

/**
 * @brief A class representing any Special object
 * 
 */
class Special : public Object {
public:
    /**
     * @brief Construct a new Special object
     * 
     * @param x An X position of new Bomb
     * @param y An Y position of new Bomb
     * @param window Window, where object is displayed
     */
    Special(int x, int y, WINDOW* window);

    /**
     * @brief If Special object is picked up gives the Player picking it it's bonus 
     * 
     */
    virtual int giveEffect() = 0;

    /**
     * @brief Check if something is on my position
     * @return -1 if my position would be out of map bounds
     *          1 if I collide with another object
     *          0 if my position is clear
     */
    virtual int collision() const;
private:
};