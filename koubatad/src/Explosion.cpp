#include "Explosion.hpp"

Explosion::Explosion(int x, int y, WINDOW *window)
        : Special(x, y, window, 2700)
{}
//----------------------------------------------------------------------------------------------

bool Explosion::drawObj() const
{
    if ( m_Exist ) {
        wattron(m_Window, COLOR_PAIR(2));
        mvwprintw(m_Window, m_Y, m_X, "%c", m_Repr);
        wattroff(m_Window, COLOR_PAIR(2));
    }
    else
        mvwprintw(m_Window, m_Y, m_X, " ");
    return m_Exist;
}
//----------------------------------------------------------------------------------------------

int Explosion::giveEffect()
{
    return DAMAGE;
}
//----------------------------------------------------------------------------------------------
