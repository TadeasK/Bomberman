#include "Wall.hpp"

Wall::Wall( int x, int y, WINDOW* window )
: Object ( x, y, window)
{}

void Wall::drawObj() const
{
    wattron(m_Window, COLOR_PAIR(1));
    mvwprintw(m_Window,m_Y, m_X, "%c", m_Repr);
    wattroff(m_Window, COLOR_PAIR(1));
}
