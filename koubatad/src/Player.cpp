#include "Player.hpp"


Player::Player( int x, int y, int speed, int bombRadius, int bombsCount, int bombThrow, int bombTimer)
: Entity( x, y, speed)
{
    m_BombRadius = bombRadius;
    m_BombsCount = bombsCount;
    m_BombThrow = bombThrow;
    m_BombTimer = bombTimer;
}

bool Player::drawObj() const
{
    wattron(stdscr, COLOR_PAIR(4));
    mvprintw(m_Y, m_X, "%c", m_Repr);
    wattroff(stdscr, COLOR_PAIR(4));
}

void Player::move()
{
    
}

bool Player::placeBomb ()
{
    // TODO Throw at player pos + throw dist (method deciding face direction)
    //      set bomb radius, add bombs placed
    if ( m_BombsPlaced.size() >= m_BombsCount )
        return false;

    int bombX = m_X, bombY = m_Y; // + m_BombThrow
    m_BombsPlaced.emplace_back( Bomb(bombX, bombY, m_BombTimer, m_BombRadius) );
    return true;
}
