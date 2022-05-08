#pragma once

#include "Special.hpp"

class BuffRadius: public Special
{
public:
    BuffRadius(int x, int y);
    ~BuffRadius() {};

    virtual bool drawObj() const override;
};