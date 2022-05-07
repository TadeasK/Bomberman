#pragma once

#include "Object.hpp"

/**
 * @brief A class representing any Special object
 * 
 */
class Special: public Object
{
public:
    /**
     * @brief Construct a new Special object
     * 
     * @param x An X position of new Bomb
     * @param y An Y position of new Bomb
     */
    Special( int x, int y );
    virtual ~Special() = default;

    virtual bool drawObj() const override;

private:
    /* data */
};