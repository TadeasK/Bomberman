#include "Enemy.hpp"

Enemy::Enemy(int x, int y, WINDOW *window, int speed)
        : Entity(x, y, window, speed) {}

void Enemy::drawObj() const {
    wattron(stdscr, COLOR_PAIR(7));
    mvwprintw(m_Window, m_Y, m_X, "%c", m_Repr);
    wattroff(stdscr, COLOR_PAIR(7));
}
//----------------------------------------------------------------------------------------------

void Enemy::move() {
}
//----------------------------------------------------------------------------------------------

bool Enemy::checkConstrains(int x, int y) {
    return true;
}