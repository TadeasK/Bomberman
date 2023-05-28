#include "BuffRadius.hpp"

BuffRadius::BuffRadius( int x, int y )
: Special (x,y)
{}

// TODO
bool BuffRadius::drawObj() const
{

}

int BuffRadius::giveEffect()
{
    return RADIUS_INC;
}
