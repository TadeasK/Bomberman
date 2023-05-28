#include "Explosion.hpp"

Explosion::Explosion(int x, int y, WINDOW *window)
        : Special(x, y, window)
{}
//----------------------------------------------------------------------------------------------

bool Explosion::drawObj() const
{
    wattron(m_Window, COLOR_PAIR(2));
    mvwprintw(m_Window, m_Y, m_X, "%c", m_Repr);
    wattroff(m_Window, COLOR_PAIR(2));
    return m_Exist;
}
//----------------------------------------------------------------------------------------------

int Explosion::giveEffect()
{
    return EXPLOSION;
}
//----------------------------------------------------------------------------------------------
