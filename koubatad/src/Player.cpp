#include "Player.hpp"

Player::Player( int x, int y, int speed, int bombRadius, int bombsCount)
: Entity( x, y, speed)
{
    m_BombRadius = bombRadius;
    m_BombsCount = bombsCount;
}

bool Player::drawObj() const
{

}

void Player::move()
{
    
}

bool Player::placeBomb ()
{
    // TODO Throw at player pos + throw dist
    //      set bomb radius, add bombs placed
    return true;
}
