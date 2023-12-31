#include "Special.hpp"

Special::Special(int x, int y, WINDOW *window, int lifeSpan)
        : Object(x, y, window)
{
    m_LifeSpan = lifeSpan;
}
//----------------------------------------------------------------------------------------------

int Special::collision() const
{
    if (m_X <= 0 || m_Y <= 0 || m_X >= GAME_WINDOW_WIDTH - 1 || m_Y >= GAME_WINDOW_HEIGHT - 1)
        return -1; // out of bounds
    chtype screenObj = mvwinch(m_Window, m_Y, m_X);
    chtype screenChar = screenObj & A_CHARTEXT;
    if (screenChar == '@' || screenChar == '$') // Player picked up bonus or Enemy destroyed bonus
        return 1;
    return 0; // No possible interaction
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
    if (m_LifeSpan < 10000)
        m_Attr = A_BLINK;
    else
        m_Attr = A_NORMAL;
}
//----------------------------------------------------------------------------------------------

