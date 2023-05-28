#include "BuffRadius.hpp"

BuffRadius::BuffRadius(int x, int y, WINDOW *window)
        : Special(x, y, window)
{}
//----------------------------------------------------------------------------------------------

// TODO
bool BuffRadius::drawObj() const
{

    return m_Exist;
}
//----------------------------------------------------------------------------------------------

int BuffRadius::giveEffect()
{
    return RADIUS_INC;
}
//----------------------------------------------------------------------------------------------
