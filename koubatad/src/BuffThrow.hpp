#pragma once

#include "Special.hpp"

class BuffThrow: public Special
{
public:
    BuffThrow(int x, int y);
    ~BuffThrow() {};

    virtual bool drawObj() const override;
};