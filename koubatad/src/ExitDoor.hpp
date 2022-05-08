#pragma once

#include "Special.hpp"

/**
 * @brief A class representing special object which leads player to next level 
 * 
 */
class ExitDoor: public Special
{
public:
    /**
     * @brief Construct a new Exit Door object
     * 
     * @param x A X position of the door
     * @param y An Y position of the door
     */
    ExitDoor(int x, int y);
    ~ExitDoor() {};

    virtual bool drawObj() const override;
    virtual void giveEffect() override;
};