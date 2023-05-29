#include "Special.hpp"

Special::Special(int x, int y, WINDOW *window, int lifeSpan)
        : Object(x, y, window)
{
    m_LifeSpan = lifeSpan;
}
//----------------------------------------------------------------------------------------------

int Special::collision() const
{
    if (m_X < 0 || m_Y < 0 || m_X > GAME_WINDOW_WIDTH || m_Y > GAME_WINDOW_HEIGHT)
        return -1;
    chtype screenObj = mvwinch(m_Window, m_Y, m_X);
    chtype screenChar = screenObj & A_CHARTEXT;
    if ( screenChar == 'X')
        return -1;
    if (screenChar == ' ')
        return 0;
    return 1;
}
//----------------------------------------------------------------------------------------------

int Special::update()
{
    reduceLifeSpan();
    return collision();
}
//----------------------------------------------------------------------------------------------

void Special::reduceLifeSpan()
{
    if (--m_LifeSpan <= 0)
        m_Exist = false;
}
//----------------------------------------------------------------------------------------------

