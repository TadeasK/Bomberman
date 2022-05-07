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
     * @param full Boolean value of whether Crate contains anything or not
     */
    Crate(int x, int y, bool full);
  
    /**
     * @brief Destroy the Crate object
     *
     */
    ~Crate();

    virtual bool drawObj() const override;

private:
    /**
     * @brief When the crate is destroyed, if it is filled drop a bonus
     *
     */
    void dropBonus();

    bool m_Filled; // Attribute containing info about whether the object has bonus inside or not
};