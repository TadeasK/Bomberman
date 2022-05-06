#pragma once

#include "Object.hpp"

/**
 * @brief A class representing Crate object 
 * 
 */
class Crate: public Object
{
public:
    /**
     * @brief Construct a new Crate object
     * 
     * @param x An X position of new Crate
     * @param y An Y position of new Crate
     * @param full Boolean value of whether Crate contains anything or not
     */
    Crate( int x, int y, bool full);

private:
    bool m_Filled;
};