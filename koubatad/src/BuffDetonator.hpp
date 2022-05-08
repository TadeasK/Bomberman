#pragma once

#include "Special.hpp"

class BuffDetonator: public Special
{
public:
    BuffDetonator(int x, int y);
    ~BuffDetonator() {};

    virtual bool drawObj() const override;
};