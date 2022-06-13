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

private:
    int count = 0;
    enum STATE_OPTIONS {
        MOVE_UP = 1, MOVE_LEFT, MOVE_DOWN, MOVE_RIGHT
    };
    int m_State = 1; // State of Enemy
    const char m_Repr = '$';

    bool checkConstrains(int x, int y) override;
};