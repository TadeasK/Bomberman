#include "BuffHeal.hpp"

BuffHeal::BuffHeal( int x, int y ,WINDOW* window)
: Special (x,y, window)
{}

// TODO
bool BuffHeal::drawObj() const
{

}

int BuffHeal::giveEffect()
{
    return HEAL;
}