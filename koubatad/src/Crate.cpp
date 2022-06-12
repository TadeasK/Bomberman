#include "Crate.hpp"

Crate::Crate ( int x, int y, WINDOW* window, bool full )
: Object ( x, y, window )
{
    m_Filled = full;
}

void Crate::drawObj() const
{
    wattron(m_Window, COLOR_PAIR(6));
    mvwprintw(m_Window,m_Y, m_X, "%c", m_Repr);
    wattroff(m_Window, COLOR_PAIR(6));
}