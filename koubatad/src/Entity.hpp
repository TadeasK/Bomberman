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
     * @param speed Movement speed of Entity
     */
    Entity( int x, int y, int speed);
    virtual ~Entity () = default;

    virtual bool drawObj() const override;
    
    /**
     * @brief Moves the entity 
     * 
     */
    virtual void move( /*Parameter defining the direction of moving*/ ) = 0;

protected:
    int m_Speed; // Speed of entity
};