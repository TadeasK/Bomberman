#include "BuffHeal.hpp"

BuffHeal::BuffHeal(int x, int y, WINDOW *window, int activeTime)
        : Special(x, y, window, activeTime)
{}

//----------------------------------------------------------------------------------------------
bool BuffHeal::drawObj() const
{
    if (m_Exist) {
        wattron(m_Window, COLOR_PAIR(3) | m_Attr);
        mvwprintw(m_Window, m_Y, m_X, "%c", m_Repr);
        wattroff(m_Window, COLOR_PAIR(3) | m_Attr);
    }
    else
        mvwprintw(m_Window, m_Y, m_X, " ");
    return m_Exist;
}
//----------------------------------------------------------------------------------------------

int BuffHeal::giveEffect()
{
    m_Exist = false;
    return HEAL;
}
//----------------------------------------------------------------------------------------------
