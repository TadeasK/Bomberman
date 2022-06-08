#include "Wall.hpp"

Wall::Wall( int x, int y )
: Object ( x, y)
{}

bool Wall::drawObj() const
{
    wattron(stdscr, COLOR_PAIR(1));
    mvprintw(m_Y, m_X, "%c", m_Repr);
    wattroff(stdscr, COLOR_PAIR(1));
}
