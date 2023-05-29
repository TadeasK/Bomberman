#include "BuffRadius.hpp"

BuffRadius::BuffRadius(int x, int y, WINDOW *window)
        : Special(x, y, window)
{}

//----------------------------------------------------------------------------------------------
bool BuffRadius::drawObj() const
{
    wattron(m_Window, COLOR_PAIR(3));
    mvwprintw(m_Window, m_Y, m_X, "%c", m_Repr);
    wattroff(m_Window, COLOR_PAIR(3));
    return m_Exist;
}
//----------------------------------------------------------------------------------------------

int BuffRadius::giveEffect()
{
    m_Exist = false;
    return RADIUS_INC;
}
//----------------------------------------------------------------------------------------------
