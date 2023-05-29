#include "BuffBomb.hpp"

BuffBomb::BuffBomb(int x, int y, WINDOW *window)
        : Special(x, y, window)
{}

//----------------------------------------------------------------------------------------------
bool BuffBomb::drawObj() const
{
    wattron(m_Window, COLOR_PAIR(3));
    mvwprintw(m_Window, m_Y, m_X, "%c", m_Repr);
    wattroff(m_Window, COLOR_PAIR(3));
    return m_Exist;
}

//----------------------------------------------------------------------------------------------
int BuffBomb::giveEffect()
{
    m_Exist = false;
    return BOMB_INC;
}
//----------------------------------------------------------------------------------------------
