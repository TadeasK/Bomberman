#pragma once

#include "Entity.hpp"

/**
 * @brief A class representing Enemy (AI controlled) entity 
 * 
 */
class Enemy: public Entity
{
public:
    /**
     * @brief Construct a new Enemy object
     * 
     * @param x An X position of new Enemy
     * @param y An Y position of new Enemy
     * @param speed Movement speed of Enemy 
     */
    Enemy( int x, int y, int speed );
    
    /**
     * @brief Destroy the Enemy object
     * 
     */
    virtual ~Enemy() = default;

    virtual bool drawObj() const;

    virtual void move();

private:
    const char m_Repr = '$';
};