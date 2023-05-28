#include "BuffDetonator.hpp"

BuffDetonator::BuffDetonator( int x, int y )
: Special (x,y)
{}

// TODO
bool BuffDetonator::drawObj() const
{

}

int BuffDetonator::giveEffect()
{
   return DETONATOR;
}