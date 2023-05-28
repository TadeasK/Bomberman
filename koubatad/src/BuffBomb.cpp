#include "BuffBomb.hpp"

BuffBomb::BuffBomb( int x, int y, WINDOW*window )
: Special (x,y,window)
{}
// TODO
bool BuffBomb::drawObj() const
{

}

int BuffBomb::giveEffect()
{
  return BOMB_INC;
}