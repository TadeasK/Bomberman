#pragma once

#include "Special.hpp"

class BuffBomb: public Special
{
public:
    BuffBomb(int x, int y);
    ~BuffBomb() {};

    virtual bool drawObj() const override;
};