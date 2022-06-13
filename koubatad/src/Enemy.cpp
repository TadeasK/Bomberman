#include "Enemy.hpp"

Enemy::Enemy(int x, int y, WINDOW *window, int speed)
        : Entity(x, y, window, speed) {}

void Enemy::drawObj() const {
    wattron(m_Window, COLOR_PAIR(7));
    mvwprintw(m_Window, m_Y, m_X, "%c", m_Repr);
    wattroff(m_Window, COLOR_PAIR(7));
}
//----------------------------------------------------------------------------------------------

void Enemy::move() {
    if ( count < 1000 ) {
        count++;
        return;
    }
    count =0;
    switch (m_State) {
        case MOVE_UP:
            if (checkConstrains(m_X, m_Y - m_Speed)) {
                mvwprintw(m_Window, m_Y, m_X, " ");
                m_Y -= m_Speed;
                break;
            } else
                m_State++;
        case MOVE_LEFT:
            if (checkConstrains(m_X - m_Speed, m_Y)) {
                mvwprintw(m_Window, m_Y, m_X, " ");
                m_X -= m_Speed;
                break;
            } else
                m_State++;
        case MOVE_DOWN:
            if (checkConstrains(m_X, m_Y + m_Speed)) {
                mvwprintw(m_Window, m_Y, m_X, " ");
                m_Y += m_Speed;
                break;
            } else
                m_State++;
        case MOVE_RIGHT:
            if (checkConstrains(m_X + m_Speed, m_Y)) {
                mvwprintw(m_Window, m_Y, m_X, " ");
                m_X += m_Speed;
                break;
            } else
                m_State = 1;
    }
}
//----------------------------------------------------------------------------------------------

bool Enemy::checkConstrains(int x, int y) {
    if (x < 0 || y < 0 || x > GAME_WINDOW_WIDTH || y > GAME_WINDOW_HEIGHT)
        return false;
    chtype screenObj = mvwinch(m_Window, y, x);
    chtype screenChar = screenObj & A_CHARTEXT;
    switch (screenChar) {
        case ' ':
            return true;
        default:
            return false;
    }
}