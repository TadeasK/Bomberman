#include "Crate.hpp"

Crate::Crate ( int x, int y, bool full )
: Object ( x, y )
{
    m_Filled = full;
}