#include "BuffLevitate.hpp"

BuffLevitate::BuffLevitate(int x, int y, WINDOW *window)
        : Special(x, y, window)
{}

//----------------------------------------------------------------------------------------------
// TODO
bool BuffLevitate::drawObj() const
{

    return m_Exist;
}
//----------------------------------------------------------------------------------------------

int BuffLevitate::giveEffect()
{
    return LEVITATE;
}
//----------------------------------------------------------------------------------------------
