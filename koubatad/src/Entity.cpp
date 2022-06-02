#include "Entity.hpp"

Entity::Entity ( int x, int y, int speed )
: Object( x, y )
{
    m_Speed = speed;
}

Entity::~Entity() {}