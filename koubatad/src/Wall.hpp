#pragma once

#include "Object.hpp"

/**
 * @brief A class representing Wall object
 * 
 */
class Wall: public Object
{
public:
    /**
     * @brief Construct a new Wall object
     * 
     * @param x An X position of new Wall
     * @param y An Y position of new Wall
     */
    Wall( int x, int y );
    ~Wall () {};

    virtual bool drawObj() const override;
    
private:
    const char m_Repr = 'X'; // Char representing Wall
};