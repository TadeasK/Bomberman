#include "BuffDetonator.hpp"

BuffDetonator::BuffDetonator(int x, int y, WINDOW *window)
        : Special(x, y, window)
{}
//----------------------------------------------------------------------------------------------

// TODO
bool BuffDetonator::drawObj() const
{
    return m_Exist;
}
//----------------------------------------------------------------------------------------------

int BuffDetonator::giveEffect()
{
    return DETONATOR;
}
//----------------------------------------------------------------------------------------------
