#include "Crate.hpp"

Crate::Crate ( int x, int y, bool full )
: Object ( x, y )
{
    m_Filled = full;
}

Crate::~Crate() {    
    if ( m_Filled )
        dropBonus();
}

bool Crate::drawObj() const
{
    wattron(stdscr, COLOR_PAIR(6));
    mvprintw(m_Y, m_X, "%c", m_Repr);
    wattroff(stdscr, COLOR_PAIR(6));
}

void Crate::dropBonus()
{

}