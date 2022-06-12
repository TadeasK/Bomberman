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
    Enemy( int x, int y,WINDOW * window, int speed );
    
    void drawObj() const override;

    void move() override;

    bool checkConstrains(int x, int y) override;
private:
    const char m_Repr = '$';
};