#include "Entity.hpp"

Entity::Entity ( int x, int y, WINDOW* window, int speed )
: Object( x, y, window )
{
    m_Speed = speed;
}