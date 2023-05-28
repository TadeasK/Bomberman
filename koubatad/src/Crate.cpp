#include "Crate.hpp"

Crate::Crate ( int x, int y, WINDOW* window, bool full )
: Object ( x, y, window )
{
    m_Filled = full;
}

bool Crate::drawObj() const
{
    wattron(m_Window, COLOR_PAIR(6));
    mvwprintw(m_Window,m_Y, m_X, "%c", m_Repr);
    wattroff(m_Window, COLOR_PAIR(6));
    return m_Exist;
}

void Crate::receiveEffect(int effect)
{
    if ( effect == EXPLOSION ) {
        m_Exist = false;
    }
}