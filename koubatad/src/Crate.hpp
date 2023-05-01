#pragma once

#include "Object.hpp"

/**
 * @brief A class representing Crate object
 *
 */
class Crate : public Object
{
public:

    /**
     * @brief Construct a new Crate object
     *
     * @param x An X position of new Crate
     * @param y An Y position of new Crate
     * @param window Window, where object is displayed
     * @param full Boolean value of whether Crate contains anything or not
     */
    Crate(int x, int y, WINDOW* window, bool full);
  
    virtual void drawObj() const override;

private:
    const char m_Repr = '#';
    bool m_Filled; // Attribute containing info about whether the object has bonus inside or not

};