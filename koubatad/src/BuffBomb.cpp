#include "BuffBomb.hpp"

BuffBomb::BuffBomb( int x, int y, WINDOW*window )
: Special (x,y,window)
{}
// TODO
bool BuffBomb::drawObj() const
{
    return m_Exist;
}

int BuffBomb::giveEffect()
{
  return BOMB_INC;
}