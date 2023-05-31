#include "Object.hpp"

Object::Object(int x, int y, WINDOW *window)
{
    m_X = x;
    m_Y = y;
    m_Window = window;
}
//----------------------------------------------------------------------------------------------

void Object::receiveEffect(int effect)
{}
//----------------------------------------------------------------------------------------------

std::pair<int, int> Object::getPosition() const
{
    return {m_X, m_Y};
}
//----------------------------------------------------------------------------------------------

