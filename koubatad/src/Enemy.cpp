#include "Enemy.hpp"

Enemy::Enemy ( int x, int y, int speed )
: Entity ( x, y, speed )
{}

bool Enemy::drawObj() const
{
    wattron(stdscr, COLOR_PAIR(3));
    mvprintw(m_Y, m_X, "%c", m_Repr);
    wattroff(stdscr, COLOR_PAIR(3));
}

void Enemy::move()
{

}