#include "Bomb.hpp"

Bomb::Bomb( int x, int y, int timer, int radius )
: Object( x, y ) 
{
    m_Timer = timer;
    m_Radius = radius;
}