#include "Object.hpp"

Object::Object ( int x, int y )
{
    m_X = x;
    m_Y = y;
}

bool Object::drawObj()
{
    return true;
}