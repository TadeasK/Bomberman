#pragma once

#include "Special.hpp"

class ExitDoor: public Special
{
public:
    ExitDoor(int x, int y);
    ~ExitDoor() {};

    virtual bool drawObj() const override;
};