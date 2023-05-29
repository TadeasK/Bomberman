#include "BuffHeal.hpp"

BuffHeal::BuffHeal(int x, int y, WINDOW *window)
        : Special(x, y, window)
{}

//----------------------------------------------------------------------------------------------
bool BuffHeal::drawObj() const
{
    wattron(m_Window, COLOR_PAIR(3));
    mvwprintw(m_Window, m_Y, m_X, "%c", m_Repr);
    wattroff(m_Window, COLOR_PAIR(3));
    return m_Exist;
}
//----------------------------------------------------------------------------------------------

int BuffHeal::giveEffect()
{
    m_Exist = false;
    return HEAL;
}
//----------------------------------------------------------------------------------------------
