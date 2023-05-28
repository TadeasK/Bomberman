#pragma once

#include "Object.hpp"

/**
 * @brief A class representing any Entity object
 * 
 */
class Entity: public Object
{
public:
    /**
     * @brief Construct a new Entity object
     * 
     * @param x An X position of new Entity
     * @param y An Y position of new Entity
     * @param window Window, where object is displayed
     * @param speed Movement speed of Entity
     */
    Entity( int x, int y, WINDOW* window, int speed);

    /**
     * @brief Moves the entity 
     * 
     */
    virtual void move() = 0;

    /**
     * @brief Check if place defined by the x,y coordinates is free
     * @param x X coordinate
     * @param y Y coordinate
     * @return True if place is free
     */
    virtual bool checkConstrains( int x, int y) = 0;

protected:
    int m_Speed; // Speed of entity
};