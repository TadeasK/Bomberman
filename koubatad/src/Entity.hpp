#pragma once

#include "Object.hpp"

class Entity: public Object
{
public:
    /**
     * @brief Construct a new Entity object
     * 
     * @param x An X position of new Entity
     * @param y An Y position of new Entity
     * @param speed Movement speed of Entity
     */
    Entity( int x, int y, int speed);
private:
    int m_Speed;
};