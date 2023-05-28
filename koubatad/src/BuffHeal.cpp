#include "BuffThrow.hpp"

BuffThrow::BuffThrow( int x, int y )
: Special (x,y)
{}

// TODO
bool BuffHeal::drawObj() const
{

}

int BuffHeal::giveEffect()
{
    return HEAL;
}