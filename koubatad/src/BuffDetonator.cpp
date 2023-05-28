#include "BuffDetonator.hpp"

BuffDetonator::BuffDetonator( int x, int y, WINDOW* window )
: Special (x,y, window)
{}

// TODO
bool BuffDetonator::drawObj() const
{

}

int BuffDetonator::giveEffect()
{
   return DETONATOR;
}