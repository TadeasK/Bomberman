#include "Bomb.hpp"

Bomb::Bomb( int x, int y, int timer, int radius )
: Object( x, y ) 
{
    m_Timer = timer;
    m_Radius = radius;
}

bool Bomb::drawObj() const
{
    wattron(stdscr, COLOR_PAIR(1));
    mvprintw(m_Y, m_X, "%d", m_Timer);
    wattroff(stdscr, COLOR_PAIR(1));
}

void Bomb::countDown()
{

}

void Bomb::explode()
{
    
}