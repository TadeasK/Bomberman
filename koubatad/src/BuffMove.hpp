#pragma once

#include "Special.hpp"

class BuffMove: public Special
{
public:
    BuffMove(int x, int y);
    ~BuffMove() {};

    virtual bool drawObj() const override;
};