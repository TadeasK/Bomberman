#include "Explosion.hpp"

Explosion::Explosion(int x, int y, WINDOW *window, int activeTime)
        : Special(x, y, window, activeTime)
{}
//----------------------------------------------------------------------------------------------

bool Explosion::drawObj() const
{
    if (m_Exist) {
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
    if (m_X <= 0 || m_Y <= 0 || m_X >= GAME_WINDOW_WIDTH - 1 || m_Y >= GAME_WINDOW_HEIGHT - 1)
        return -1; // out of bounds
    chtype screenObj = mvwinch(m_Window, m_Y, m_X);
    chtype screenChar = screenObj & A_CHARTEXT;
    if (screenChar == 'X') // No possible interaction
        return -1;
    if (screenChar == ' ') // Nothing in the way
        return 0;
    return 1; // Collided with something
}
//----------------------------------------------------------------------------------------------

int Explosion::giveEffect()
{
    return EXPLOSION;
}
//----------------------------------------------------------------------------------------------
