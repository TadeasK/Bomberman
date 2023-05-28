#include "Special.hpp"

Special::Special(int x, int y, WINDOW *window)
        : Object(x, y, window) {}

int Special::collision() const {
    if (m_X < 0 || m_Y < 0 || m_X > GAME_WINDOW_WIDTH || m_Y > GAME_WINDOW_HEIGHT)
        return -1;
    chtype screenObj = mvwinch(m_Window, m_Y, m_X);
    chtype screenChar = screenObj & A_CHARTEXT;
    if ( screenChar != ' ' )
        return 1;
    return 0;
}

