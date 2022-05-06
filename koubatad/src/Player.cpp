#include "Player.hpp"

Player::Player( int x, int y, int speed, int bombRadius, int bombsCount, int bombThrow )
: Entity( x, y, speed)
{
    m_BombRadius = bombRadius;
    m_BombsCount = bombsCount;
    m_BombThrow = bombThrow;
}

bool Player::placeBomb ()
{
    // TODO Throw at player pos + throw dist
    //      set bomb radius, add bombs placed
    return true;
}
