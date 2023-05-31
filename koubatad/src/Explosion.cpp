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

int Explosion::collision() const
{
    if (m_X < 0 || m_Y < 0 || m_X > GAME_WINDOW_WIDTH || m_Y > GAME_WINDOW_HEIGHT)
        return -1;
    chtype screenObj = mvwinch(m_Window, m_Y, m_X);
    chtype screenChar = screenObj & A_CHARTEXT;
    if ( screenChar == 'X')
        return -1;
    if (screenChar == ' ')
        return 0;
    return 1;
}
//----------------------------------------------------------------------------------------------

int Explosion::giveEffect()
{
    return EXPLOSION;
}
//----------------------------------------------------------------------------------------------
