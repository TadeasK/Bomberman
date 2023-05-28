#include "BuffHeal.hpp"

BuffHeal::BuffHeal( int x, int y ,WINDOW* window)
: Special (x,y, window)
{}

// TODO
bool BuffHeal::drawObj() const
{
    return m_Exist;

}

int BuffHeal::giveEffect()
{
    return HEAL;
}