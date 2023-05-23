#include "Bomb.hpp"

Bomb::Bomb( int x, int y,WINDOW* window, int timer, int radius )
: Object( x, y, window )
{
    m_Timer = timer;
    m_Radius = radius;
}

void Bomb::drawObj() const
{
    wattron(m_Window, COLOR_PAIR(8));
    mvwprintw(m_Window,m_Y, m_X, "%d", m_Timer);
    wattroff(m_Window, COLOR_PAIR(8));
}
// TODO
void Bomb::countDown()
{

}

void Bomb::explode()
{
    
}